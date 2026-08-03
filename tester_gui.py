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
            return -1, f"Erro: Executável '{self.executable_path}' não encontrado no diretório atual."

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
            
            moves = len(stdout_output.split('\n')) if stdout_output else 0
            
            if result.returncode != 0:
                return -1, f"Erro na execução (Código {result.returncode}):\n{stderr_output}"
                
            return moves, stderr_output if stderr_output else "(Nenhuma saída de erro/bench detectada no stderr)"
            
        except subprocess.TimeoutExpired:
            return -1, "Erro: Tempo limite de execução excedido (Timeout 10s)."
        except Exception as e:
            return -1, f"Erro inesperado: {str(e)}"

# ==========================================
# MÓDULO 3: INTERFACE GRÁFICA (GUI)
# ==========================================
class PushSwapGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Push_Swap Visual Tester")
        self.root.geometry("700x750")
        self.root.configure(padx=20, pady=20)
        
        # Variáveis de Controle
        self.size_var = tk.IntVar(value=100)
        self.disorder_var = tk.IntVar(value=100)
        self.bench_var = tk.BooleanVar(value=False)
        self.difficulty_var = tk.StringVar(value="Nenhuma")
        
        self.tester = PushSwapTester()
        self.setup_ui()

    def setup_ui(self):
        # Estilo Global
        style = ttk.Style()
        style.configure("TButton", font=("Helvetica", 10, "bold"), padding=6)
        style.configure("TLabelframe.Label", font=("Helvetica", 10, "bold"), foreground="#333333")

        # --- SEÇÃO 1: GERADOR ---
        frame_gen = ttk.LabelFrame(self.root, text=" ⚙️ Configurações do Gerador ", padding=15)
        frame_gen.pack(fill="x", pady=(0, 15))

        ttk.Label(frame_gen, text="Tamanho da Pilha (Qtd):").grid(row=0, column=0, sticky="w", pady=5)
        ttk.Entry(frame_gen, textvariable=self.size_var, width=15).grid(row=0, column=1, sticky="w", pady=5, padx=10)

        ttk.Label(frame_gen, text="Desordem:").grid(row=1, column=0, sticky="w", pady=10)
        
        # Frame interno para o slider
        slider_frame = ttk.Frame(frame_gen)
        slider_frame.grid(row=1, column=1, columnspan=2, sticky="we", padx=10)
        
        self.slider = ttk.Scale(slider_frame, from_=0, to=100, orient="horizontal", variable=self.disorder_var, command=self.update_slider_label)
        self.slider.pack(side="left", fill="x", expand=True)
        
        self.slider_label = ttk.Label(slider_frame, text="100%", font=("Helvetica", 10, "bold"), width=5)
        self.slider_label.pack(side="left", padx=(10, 0))

        # --- SEÇÃO 2: PARÂMETROS DO PUSH_SWAP ---
        frame_flags = ttk.LabelFrame(self.root, text=" 🛠️ Parâmetros de Execução ", padding=15)
        frame_flags.pack(fill="x", pady=(0, 15))

        ttk.Checkbutton(frame_flags, text="Ativar Modo Benchmark (--bench)", variable=self.bench_var).pack(anchor="w", pady=5)

        flag_frame = ttk.Frame(frame_flags)
        flag_frame.pack(fill="x", pady=5)
        ttk.Label(flag_frame, text="Complexidade:").pack(side="left")
        
        options = ["Nenhuma", "Simple", "Medium", "Complex"]
        ttk.OptionMenu(flag_frame, self.difficulty_var, options[0], *options).pack(side="left", padx=10)

        # --- BOTÃO PRINCIPAL ---
        self.run_btn = ttk.Button(self.root, text="▶ GERAR NÚMEROS E TESTAR", command=self.run_process)
        self.run_btn.pack(fill="x", pady=10, ipady=5)

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
        # Atualiza a label do slider ignorando casas decimais
        val = int(float(self.disorder_var.get()))
        self.slider_label.config(text=f"{val}%")

    def set_text_widget(self, widget, content):
        """Função auxiliar para atualizar caixas de texto com segurança"""
        widget.config(state="normal")
        widget.delete(1.0, tk.END)
        widget.insert(tk.END, content)
        widget.config(state="disabled")

    def run_process(self):
        try:
            size = self.size_var.get()
            if size <= 0:
                messagebox.showerror("Erro", "O tamanho da pilha deve ser maior que zero.")
                return
        except ValueError:
            messagebox.showerror("Erro", "Tamanho inválido. Digite um número inteiro.")
            return

        # Interface em modo de "carregamento"
        self.run_btn.config(text="⏳ EXECUTANDO...", state="disabled")
        self.moves_label.config(text="Calculando...", foreground="blue")
        self.root.update() # Força a interface a atualizar antes de rodar o processo pesado

        # 1. Gerar números
        disorder = self.disorder_var.get()
        numbers = NumberGenerator.generate(size, disorder)

        preview_nums = numbers[:20]
        preview_str = " ".join(map(str, preview_nums)) + ("..." if size > 20 else "")
        self.set_text_widget(self.args_text, preview_str)

        # 2. Executar teste
        use_bench = self.bench_var.get()
        difficulty = self.difficulty_var.get()
        
        moves, stderr_output = self.tester.run_test(numbers, use_bench, difficulty)

        # 3. Mostrar resultados
        if moves == -1:
            self.moves_label.config(text="❌ FALHA NA EXECUÇÃO", foreground="red")
        else:
            color = "green" if (size <= 100 and moves < 700) or (size <= 500 and moves < 5500) else "red"
            self.moves_label.config(text=f"✓ Movimentos: {moves}", foreground=color)

        self.set_text_widget(self.output_text, stderr_output)

        # Restaura o botão
        self.run_btn.config(text="▶ GERAR NÚMEROS E TESTAR", state="normal")

if __name__ == "__main__":
    root = tk.Tk()
    style = ttk.Style()
    if "clam" in style.theme_names():
        style.theme_use("clam")
    app = PushSwapGUI(root)
    root.mainloop()