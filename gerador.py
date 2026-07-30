import os
import random
import sys

# Cores para o terminal
CYAN = '\033[96m'
GREEN = '\033[92m'
YELLOW = '\033[93m'
RED = '\033[91m'
RESET = '\033[0m'

def limpar_tela():
    os.system('cls' if os.name == 'nt' else 'clear')

def obter_inversoes_e_array(n, nivel_desordem):
    """
    Calcula a quantidade exata de inversões (mistakes) necessárias
    e constrói o array puxando elementos de uma lista ordenada.
    """
    max_pares = n * (n - 1) // 2
    
    # Define um alvo de desordem com base no nível escolhido
    if nivel_desordem == "low":
        alvo = random.uniform(0.05, 0.15)  # < 0.2
    elif nivel_desordem == "medium":
        alvo = random.uniform(0.25, 0.45)  # 0.2 <= d < 0.5
    else:
        alvo = random.uniform(0.60, 0.90)  # >= 0.5
        
    inversoes_alvo = int(max_pares * alvo)
    
    # Gera 'n' números aleatórios únicos
    limite = max(1000000, n * 10)
    numeros = random.sample(range(-limite, limite), n)
    
    # Ordena para ter 0 inversões no começo
    disponiveis = sorted(numeros)
    resultado = []
    
    inversoes_restantes = inversoes_alvo
    
    # Constrói o array com as inversões exatas
    while disponiveis:
        # O máximo de inversões que podemos criar com o próximo número
        # é colocar o maior número disponível, o que nos dá len(disponiveis) - 1 inversões.
        # Nós pegamos o número no índice 'k' para adicionar 'k' inversões.
        k = min(inversoes_restantes, len(disponiveis) - 1)
        resultado.append(disponiveis.pop(k))
        inversoes_restantes -= k
        
    return resultado, inversoes_alvo, max_pares, alvo

def main():
    qtd = 100
    nivel = "medium"
    arquivo_saida = "numeros.txt"

    opcoes_nivel = ["low", "medium", "high"]
    idx_nivel = 1

    while True:
        limpar_tela()
        print(f"{CYAN}=================================================={RESET}")
        print(f"{CYAN}       GERADOR DE DESORDEM (INVERSIONS TUI)       {RESET}")
        print(f"{CYAN}=================================================={RESET}")
        print(f" [1] Quantidade de números : {YELLOW}{qtd}{RESET}")
        print(f" [2] Nível de desordem     : {YELLOW}{nivel.upper()}{RESET} (Low < 0.2 | Medium < 0.5 | High >= 0.5)")
        print(f" [3] Arquivo de saída      : {YELLOW}{arquivo_saida}{RESET}")
        print(f" [4] {GREEN}GERAR E SALVAR{RESET}")
        print(f" [0] {RED}Sair{RESET}")
        print(f"{CYAN}=================================================={RESET}")
        
        escolha = input("\nEscolha uma opção: ")

        if escolha == '1':
            try:
                nova_qtd = int(input("Digite a quantidade de números desejada: "))
                if nova_qtd > 1:
                    qtd = nova_qtd
                else:
                    input(f"{RED}A quantidade deve ser maior que 1. Pressione Enter.{RESET}")
            except ValueError:
                pass
                
        elif escolha == '2':
            idx_nivel = (idx_nivel + 1) % 3
            nivel = opcoes_nivel[idx_nivel]
            
        elif escolha == '3':
            novo_arquivo = input("Digite o nome do arquivo (ex: numeros.txt): ")
            if novo_arquivo.strip():
                arquivo_saida = novo_arquivo.strip()
                
        elif escolha == '4':
            print("\nGerando...")
            resultado, inversoes, max_pares, alvo = obter_inversoes_e_array(qtd, nivel)
            
            try:
                with open(arquivo_saida, 'w') as f:
                    # Salva os números separados por espaço
                    f.write(" ".join(map(str, resultado)))
                
                desordem_real = inversoes / max_pares
                print(f"\n{GREEN}✓ Sucesso! Arquivo '{arquivo_saida}' gerado.{RESET}")
                print(f"   Total de elementos: {qtd}")
                print(f"   Total de pares: {max_pares}")
                print(f"   Erros (inversões): {inversoes}")
                print(f"   Desordem atingida: {YELLOW}{desordem_real:.4f}{RESET}")
                
            except Exception as e:
                print(f"\n{RED}Erro ao salvar arquivo: {e}{RESET}")
                
            input("\nPressione Enter para continuar...")
            
        elif escolha == '0':
            limpar_tela()
            sys.exit(0)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        limpar_tela()
        sys.exit(0)