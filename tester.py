import tkinter as tk
from tkinter import ttk, messagebox
import random
import subprocess
import os

# ==========================================
# MÓDULO 1: GERADOR DE NÚMEROS
# ==========================================
class NumberGenerator:
    @staticmethod
    def generate(size, disorder_percentage):
        if size <= 0:
            return []
            
        pool = sorted(random.sample(range(-50000, 50000), size))
        
        if disorder_percentage <= 0:
            return pool
        if disorder_percentage >= 100:
            return pool[::-1]
            
        max_inversions = (size * (size - 1)) // 2
        target_inversions = int(max_inversions * (disorder_percentage / 100.0))
        
        result = []
        
        while target_inversions > 0 and len(pool) > 0:
            k = len(pool)
            if target_inversions >= k - 1:
                result.append(pool.pop(-1))
                target_inversions -= (k - 1)
            else:
                result.append(pool.pop(target_inversions))
                target_inversions = 0
                
        result.extend(pool)
        return result

# ==========================================
# MÓDULO 2: TESTADOR DO PUSH_SWAP
# ==========================================
class PushSwapTester:
    def __init__(self, executable_path="./push_swap"):
        self.executable_path = executable_path

    def run_test(self, numbers, use_bench, difficulty_flag):
        if not os.path.isfile(self.executable_path):
            return -1, [], f"Erro: Executável '{self.executable_path}' não encontrado no diretório atual."

        command = [self.executable_path]
        
        if use_bench:
            command.append("--bench")
        if difficulty_flag != "Nenhuma":
            command.append(f"--{difficulty_flag.lower()}")
            
        command.extend([str(n) for n in numbers])

        try:
            result = subprocess.run(command, capture_output=True, text=True, timeout=10)
            
            stdout_output = result.stdout.strip()
            stderr_output = result.stderr.strip()
            
            moves_list = stdout_output.split('\n') if stdout_output else []
            moves = len(moves_list)
            
            if result.returncode != 0:
                return -1, [], f"Erro na execução (Código {result.returncode}):\n{stderr_output}"
                
            return moves, moves_list, stderr_output if stderr_output else "(Nenhuma saída de erro/bench detectada no stderr)"
            
        except subprocess.TimeoutExpired:
            return -1, [], "Erro: Tempo limite de execução excedido (Timeout 10s)."
        except Exception as e:
            return -1, [], f"Erro inesperado: {str(e)}"

# ==========================================
# MÓDULO 3: VISUALIZADOR ANIMADO
# ==========================================
class PushSwapVisualizer(tk.Toplevel):
    def __init__(self, parent, numbers, instructions):
        super().__init__(parent)
        self.title("Push_Swap Visualizer")
        self.geometry("900x600")
        self.configure(bg="#2b2b2b")
        
        self.numbers = numbers[:]
        
        # Filtra apenas instruções válidas para evitar crash visual
        valid_moves = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"}
        self.instructions = [i.strip() for i in instructions if i.strip() in valid_moves]
        
        self.current_step = 0
        self.is_playing = False
        self.after_id = None
        
        # Mapeamento para desenhar as alturas relativas (0 a N)
        sorted_nums = sorted(self.numbers)
        self.val_to_idx = {val: i for i, val in enumerate(sorted_nums)}
        
        self.history = []
        self.precompute_history()
        
        self.setup_ui()
        self.draw_stacks()
        self.bind("<Configure>", self.on_resize)

    def precompute_history(self):
        """Pré-computa todos os estados para permitir navegação instantânea pela linha do tempo."""
        a = self.numbers[:]
        b = []
        self.history.append((a[:], b[:], "Início"))
        
        for inst in self.instructions:
            if inst == "sa" and len(a) > 1: a[0], a[1] = a[1], a[0]
            elif inst == "sb" and len(b) > 1: b[0], b[1] = b[1], b[0]
            elif inst == "ss":
                if len(a) > 1: a[0], a[1] = a[1], a[0]
                if len(b) > 1: b[0], b[1] = b[1], b[0]
            elif inst == "pa" and len(b) > 0: a.insert(0, b.pop(0))
            elif inst == "pb" and len(a) > 0: b.insert(0, a.pop(0))
            elif inst == "ra" and len(a) > 1: a.append(a.pop(0))
            elif inst == "rb" and len(b) > 1: b.append(b.pop(0))
            elif inst == "rr":
                if len(a) > 1: a.append(a.pop(0))
                if len(b) > 1: b.append(b.pop(0))
            elif inst == "rra" and len(a) > 1: a.insert(0, a.pop())
            elif inst == "rrb" and len(b) > 1: b.insert(0, b.pop())
            elif inst == "rrr":
                if len(a) > 1: a.insert(0, a.pop())
                if len(b) > 1: b.insert(0, b.pop())
            
            self.history.append((a[:], b[:], inst))

    def setup_ui(self):
        self.canvas = tk.Canvas(self, bg="#1e1e1e", highlightthickness=0)
        self.canvas.pack(fill="both", expand=True, padx=10, pady=10)
        
        controls = tk.Frame(self, bg="#2b2b2b")
        controls.pack(fill="x", padx=10, pady=(0, 10))
        
        self.play_btn = ttk.Button(controls, text="▶ Play", command=self.toggle_play)
        self.play_btn.pack(side="left", padx=5)
        
        ttk.Button(controls, text="⏮ Início", command=lambda: self.seek(0)).pack(side="left", padx=5)
        ttk.Button(controls, text="⏭ Fim", command=lambda: self.seek(len(self.instructions))).pack(side="left", padx=5)
        
        self.timeline_var = tk.IntVar(value=0)
        self.slider = ttk.Scale(controls, from_=0, to=len(self.instructions), variable=self.timeline_var, command=self.on_slide)
        self.slider.pack(side="left", fill="x", expand=True, padx=10)
        
        ttk.Label(controls, text="Velocidade:", background="#2b2b2b", foreground="white").pack(side="left")
        self.speed_var = tk.IntVar(value=50)
        ttk.Scale(controls, from_=1, to=1000, variable=self.speed_var).pack(side="left", padx=5)

    def on_resize(self, event):
        self.draw_stacks()

    def toggle_play(self):
        self.is_playing = not self.is_playing
        if self.is_playing:
            self.play_btn.config(text="⏸ Pause")
            if self.current_step >= len(self.instructions):
                self.seek(0)
            self.run_animation()
        else:
            self.play_btn.config(text="▶ Play")
            if self.after_id:
                self.after_cancel(self.after_id)

    def on_slide(self, val):
        self.is_playing = False
        self.play_btn.config(text="▶ Play")
        self.current_step = int(float(val))
        self.draw_stacks()

    def seek(self, step):
        self.is_playing = False
        self.play_btn.config(text="▶ Play")
        self.current_step = step
        self.timeline_var.set(step)
        self.draw_stacks()

    def run_animation(self):
        if not self.is_playing: return
        
        speed = self.speed_var.get()
        # Se a velocidade for muito alta, pulamos passos para não travar a interface
        steps_per_frame = max(1, int(speed / 60))
        delay = max(1, int(1000 / speed)) if speed <= 60 else 16
        
        if self.current_step < len(self.instructions):
            self.current_step = min(len(self.instructions), self.current_step + steps_per_frame)
            self.timeline_var.set(self.current_step)
            self.draw_stacks()
            self.after_id = self.after(delay, self.run_animation)
        else:
            self.is_playing = False
            self.play_btn.config(text="▶ Play")

    def draw_stacks(self):
        self.canvas.delete("all")
        if not self.history: return
        
        a, b, last_inst = self.history[self.current_step]
        w = self.canvas.winfo_width()
        h = self.canvas.winfo_height()
        
        if w < 10 or h < 10: 
            w, h = 900, 500 # fallback
            
        # Labels
        self.canvas.create_text(w//4, 20, text=f"Stack A ({len(a)})", fill="white", font=("Helvetica", 12, "bold"))
        self.canvas.create_text(3*w//4, 20, text=f"Stack B ({len(b)})", fill="white", font=("Helvetica", 12, "bold"))
        self.canvas.create_text(w//2, 20, text=f"Movimento: {last_inst} [{self.current_step}/{len(self.instructions)}]", fill="#ffd700", font=("Helvetica", 11, "bold"))
        
        self._draw_bars(a, 10, w//2 - 5, h, "#00a8ff") # Azul para A
        self._draw_bars(b, w//2 + 5, w - 10, h, "#e84118") # Vermelho/Laranja para B

    def _draw_bars(self, stack, x_start, x_end, h, color):
        if not stack: return
        N = len(self.numbers)
        bar_w = (x_end - x_start) / N
        max_h = h - 50
        
        for i, val in enumerate(stack):
            rank = self.val_to_idx[val]
            # Altura mínima de 3 pixels, cresce até max_h de forma relativa ao tamanho do array
            bar_h = max(3, ((rank + 1) / N) * max_h)
            
            x1 = x_start + i * bar_w
            y1 = h - bar_h
            x2 = x1 + bar_w
            y2 = h
            
            self.canvas.create_rectangle(x1, y1, x2, y2, fill=color, outline="")

# ==========================================
# MÓDULO 4: INTERFACE GRÁFICA PRINCIPAL (GUI)
# ==========================================
class PushSwapGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Push_Swap Visual Tester")
        self.root.geometry("700x780")
        self.root.configure(padx=20, pady=20)
        
        self.size_var = tk.IntVar(value=100)
        self.disorder_var = tk.IntVar(value=100)
        self.bench_var = tk.BooleanVar(value=False)
        self.difficulty_var = tk.StringVar(value="Nenhuma")
        
        self.tester = PushSwapTester()
        
        # Variáveis em cache para o visualizador
        self.last_numbers = []
        self.last_instructions = []
        
        self.setup_ui()

    def setup_ui(self):
        style = ttk.Style()
        style.configure("TButton", font=("Helvetica", 10, "bold"), padding=6)
        style.configure("TLabelframe.Label", font=("Helvetica", 10, "bold"), foreground="#333333")

        # --- SEÇÃO 1: GERADOR ---
        frame_gen = ttk.LabelFrame(self.root, text=" ⚙️ Configurações do Gerador ", padding=15)
        frame_gen.pack(fill="x", pady=(0, 15))

        ttk.Label(frame_gen, text="Tamanho da Pilha (Qtd):").grid(row=0, column=0, sticky="w", pady=5)
        ttk.Entry(frame_gen, textvariable=self.size_var, width=15).grid(row=0, column=1, sticky="w", pady=5, padx=10)

        ttk.Label(frame_gen, text="Desordem:").grid(row=1, column=0, sticky="w", pady=10)
        
        slider_frame = ttk.Frame(frame_gen)
        slider_frame.grid(row=1, column=1, columnspan=2, sticky="we", padx=10)
        
        self.slider = ttk.Scale(slider_frame, from_=0, to=100, orient="horizontal", variable=self.disorder_var, command=self.update_slider_label)
        self.slider.pack(side="left", fill="x", expand=True)
        
        self.slider_label = ttk.Label(slider_frame, text="100%", font=("Helvetica", 10, "bold"), width=5)
        self.slider_label.pack(side="left", padx=(10, 0))

        # --- SEÇÃO 2: PARÂMETROS ---
        frame_flags = ttk.LabelFrame(self.root, text=" 🛠️ Parâmetros de Execução ", padding=15)
        frame_flags.pack(fill="x", pady=(0, 15))

        ttk.Checkbutton(frame_flags, text="Ativar Modo Benchmark (--bench)", variable=self.bench_var).pack(anchor="w", pady=5)

        flag_frame = ttk.Frame(frame_flags)
        flag_frame.pack(fill="x", pady=5)
        ttk.Label(flag_frame, text="Complexidade:").pack(side="left")
        
        options = ["Nenhuma", "Simple", "Medium", "Complex"]
        ttk.OptionMenu(flag_frame, self.difficulty_var, options[0], *options).pack(side="left", padx=10)

        # --- BOTÕES PRINCIPAIS ---
        btn_frame = ttk.Frame(self.root)
        btn_frame.pack(fill="x", pady=10)
        
        self.run_btn = ttk.Button(btn_frame, text="▶ GERAR NÚMEROS E TESTAR", command=self.run_process)
        self.run_btn.pack(side="left", fill="x", expand=True, ipady=5, padx=(0, 5))
        
        self.vis_btn = ttk.Button(btn_frame, text="👁️ ABRIR VISUALIZADOR", command=self.open_visualizer, state="disabled")
        self.vis_btn.pack(side="left", fill="x", expand=True, ipady=5, padx=(5, 0))

        # --- SEÇÃO 3: RESULTADOS ---
        frame_res = ttk.LabelFrame(self.root, text=" 📊 Resultados ", padding=15)
        frame_res.pack(fill="both", expand=True)

        self.moves_label = ttk.Label(frame_res, text="Aguardando teste...", font=("Helvetica", 14, "bold"), foreground="#555555")
        self.moves_label.pack(anchor="w", pady=(0, 10))

        ttk.Label(frame_res, text="Argumentos gerados (amostra):").pack(anchor="w")
        self.args_text = tk.Text(frame_res, height=2, wrap="word", state="disabled", bg="#f4f4f4", font=("Courier", 9))
        self.args_text.pack(fill="x", pady=(0, 15))

        ttk.Label(frame_res, text="Saída do Terminal (STDERR / Bench):").pack(anchor="w")
        
        scroll = ttk.Scrollbar(frame_res)
        scroll.pack(side="right", fill="y")
        
        self.output_text = tk.Text(frame_res, height=10, wrap="word", yscrollcommand=scroll.set, state="disabled", bg="#1e1e1e", fg="#00ff00", font=("Courier", 10))
        self.output_text.pack(fill="both", expand=True)
        scroll.config(command=self.output_text.yview)

    def update_slider_label(self, event):
        val = int(float(self.disorder_var.get()))
        self.slider_label.config(text=f"{val}%")

    def set_text_widget(self, widget, content):
        widget.config(state="normal")
        widget.delete(1.0, tk.END)
        widget.insert(tk.END, content)
        widget.config(state="disabled")
        
    def open_visualizer(self):
        if self.last_numbers and self.last_instructions:
            PushSwapVisualizer(self.root, self.last_numbers, self.last_instructions)

    def run_process(self):
        try:
            size = self.size_var.get()
            if size <= 0:
                messagebox.showerror("Erro", "O tamanho da pilha deve ser maior que zero.")
                return
        except ValueError:
            messagebox.showerror("Erro", "Tamanho inválido. Digite um número inteiro.")
            return

        # 1. Mutação da desordem (Varia 1% para cima ou para baixo)
        current_disorder = int(self.disorder_var.get())
        variation = random.choice([-1, 1])
        new_disorder = max(0, min(100, current_disorder + variation))
        
        self.disorder_var.set(new_disorder)
        self.update_slider_label(None)

        self.run_btn.config(text="⏳ EXECUTANDO...", state="disabled")
        self.vis_btn.config(state="disabled")
        self.moves_label.config(text="Calculando...", foreground="blue")
        self.root.update()

        # 2. Gerar números
        numbers = NumberGenerator.generate(size, new_disorder)

        preview_nums = numbers[:20]
        preview_str = " ".join(map(str, preview_nums)) + ("..." if size > 20 else "")
        self.set_text_widget(self.args_text, preview_str)

        # 3. Executar teste
        use_bench = self.bench_var.get()
        difficulty = self.difficulty_var.get()
        
        moves, moves_list, stderr_output = self.tester.run_test(numbers, use_bench, difficulty)

        # 4. Mostrar resultados
        if moves == -1:
            self.moves_label.config(text="❌ FALHA NA EXECUÇÃO", foreground="red")
        else:
            color = "green" if (size <= 100 and moves < 700) or (size <= 500 and moves < 5500) else "red"
            self.moves_label.config(text=f"✓ Movimentos: {moves}", foreground=color)
            
            # Habilita o visualizador e salva estado
            self.last_numbers = numbers
            self.last_instructions = moves_list
            self.vis_btn.config(state="normal")

        self.set_text_widget(self.output_text, stderr_output)
        self.run_btn.config(text="▶ GERAR NÚMEROS E TESTAR", state="normal")

if __name__ == "__main__":
    root = tk.Tk()
    style = ttk.Style()
    if "clam" in style.theme_names():
        style.theme_use("clam")
    app = PushSwapGUI(root)
    root.mainloop()