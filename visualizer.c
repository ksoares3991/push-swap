#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "raylib.h"

// --- ESTRUTURAS DE DADOS ---
typedef struct s_node {
    int number;
    struct s_node *next;
} t_node;

typedef struct s_stack {
    t_node *head;
    int size;
} t_stack;

typedef struct s_state {
    t_stack *a;
    t_stack *b;
} t_state;

// --- VARIÁVEIS GLOBAIS DE ESTADO ---
t_state *global_state;
pthread_mutex_t state_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t sort_thread;
bool thread_running = false;

bool sort_finished = false;
bool force_exit = false;
bool is_paused = false;

// Configurações de Janela e Execução
int window_width = 1920;  // Padrão Full HD
int window_height = 1080; // Padrão Full HD
bool is_fullscreen = false;

int delay_us = 15000;      // Delay em microssegundos (15ms padrão)
int steps_per_batch = 1;   // Número de passos por ciclo/delay

int max_elements = 50;
int max_val = 50;
int min_val = 1;
int active_target_val = -999999; // Valor em destaque pedagógico

// Explicações Didáticas
char phase_name[100] = "Aguardando";
char action_name[20] = "INÍCIO";
char action_desc[250] = "Pressione INICIAR para começar.";
char reason_desc[250] = "O algoritmo vai analisar e reorganizar a sequência passo a passo.";

// Estados e Foco na Interface
typedef enum { MENU, SORTING } AppState;
AppState current_state = MENU;

typedef enum {
    FIELD_NONE,
    FIELD_MANUAL_SEQ,
    FIELD_RES,
    FIELD_SPEED,
    FIELD_STEPS,
    FIELD_RANDOM_COUNT
} FieldID;
FieldID active_field = FIELD_NONE;

// Buffers de Entrada Manual
bool manual_input_mode = false;
char input_buffer[4096] = "42 13 8 99 3 27 1 65 12 5";
char res_buffer[32] = "1920 x 1080";
char speed_buffer[32] = "15";
char steps_buffer[32] = "1";
char random_count_buffer[32] = "50";

// Benchmarks
int total_ops = 0;
float initial_disorder = 0.0f;

// --- UTILITÁRIOS DE MEMÓRIA ---
t_node *create_node(int val) {
    t_node *new_node = malloc(sizeof(t_node));
    new_node->number = val;
    new_node->next = NULL;
    return new_node;
}

void clear_stack(t_stack *s) {
    if (!s) return;
    t_node *curr = s->head;
    while (curr) {
        t_node *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    s->head = NULL;
    s->size = 0;
}

void set_explanation(const char *phase, const char *act, const char *desc, const char *reason, int target) {
    pthread_mutex_lock(&state_mutex);
    if (phase) strncpy(phase_name, phase, sizeof(phase_name) - 1);
    if (act) strncpy(action_name, act, sizeof(action_name) - 1);
    if (desc) strncpy(action_desc, desc, sizeof(action_desc) - 1);
    if (reason) strncpy(reason_desc, reason, sizeof(reason_desc) - 1);
    active_target_val = target;
    pthread_mutex_unlock(&state_mutex);
}

// --- APLICAÇÃO DE RESOLUÇÃO E MODO DE TELA ---
void apply_resolution_and_mode() {
    int w = 1920, h = 1080;
    if (sscanf(res_buffer, "%d x %d", &w, &h) != 2 && sscanf(res_buffer, "%dx%d", &w, &h) != 2) {
        w = 1920; h = 1080;
    }
    if (w < 800) w = 800;
    if (h < 600) h = 600;

    window_width = w;
    window_height = h;

    // Atualiza a string do buffer para manter o formato padronizado
    sprintf(res_buffer, "%d x %d", window_width, window_height);

    // Altera o modo de tela se for diferente do estado atual do Raylib
    if (is_fullscreen != IsWindowFullscreen()) {
        ToggleFullscreen();
    }

    SetWindowSize(window_width, window_height);

    // Centraliza a janela na tela do monitor quando estiver em modo janela
    if (!is_fullscreen) {
        int monitor = GetCurrentMonitor();
        SetWindowPosition((GetMonitorWidth(monitor) - window_width) / 2,
                          (GetMonitorHeight(monitor) - window_height) / 2);
    }
}

// --- OPERAÇÕES DO PUSH SWAP ---
void register_op(char *name) {
    pthread_mutex_lock(&state_mutex);
    total_ops++;
    pthread_mutex_unlock(&state_mutex);
}

void end_op() {
    pthread_mutex_lock(&state_mutex);
    int current_op = total_ops;
    pthread_mutex_unlock(&state_mutex);

    while (is_paused && !force_exit) {
        usleep(20000);
    }

    if (!force_exit && (current_op % steps_per_batch == 0)) {
        if (delay_us > 0) usleep(delay_us);
    }
}

void pa(t_state *s) {
    if (!s->b->head) return;
    register_op("pa");
    t_node *tmp = s->b->head;
    s->b->head = s->b->head->next;
    s->b->size--;
    tmp->next = s->a->head;
    s->a->head = tmp;
    s->a->size++;
    end_op();
}

void pb(t_state *s) {
    if (!s->a->head) return;
    register_op("pb");
    t_node *tmp = s->a->head;
    s->a->head = s->a->head->next;
    s->a->size--;
    tmp->next = s->b->head;
    s->b->head = tmp;
    s->b->size++;
    end_op();
}

void ra(t_state *s) {
    if (!s->a->head || !s->a->head->next) return;
    register_op("ra");
    t_node *first = s->a->head;
    s->a->head = first->next;
    t_node *curr = s->a->head;
    while (curr->next) curr = curr->next;
    curr->next = first;
    first->next = NULL;
    end_op();
}

void rb(t_state *s) {
    if (!s->b->head || !s->b->head->next) return;
    register_op("rb");
    t_node *first = s->b->head;
    s->b->head = first->next;
    t_node *curr = s->b->head;
    while (curr->next) curr = curr->next;
    curr->next = first;
    first->next = NULL;
    end_op();
}

void rra(t_state *s) {
    if (!s->a->head || !s->a->head->next) return;
    register_op("rra");
    t_node *prev = NULL;
    t_node *curr = s->a->head;
    while (curr->next) { prev = curr; curr = curr->next; }
    prev->next = NULL;
    curr->next = s->a->head;
    s->a->head = curr;
    end_op();
}

void rrb(t_state *s) {
    if (!s->b->head || !s->b->head->next) return;
    register_op("rrb");
    t_node *prev = NULL;
    t_node *curr = s->b->head;
    while (curr->next) { prev = curr; curr = curr->next; }
    prev->next = NULL;
    curr->next = s->b->head;
    s->b->head = curr;
    end_op();
}

void sa(t_state *s) {
    if (!s->a->head || !s->a->head->next) return;
    register_op("sa");
    t_node *first = s->a->head;
    t_node *second = first->next;
    first->next = second->next;
    second->next = first;
    s->a->head = second;
    end_op();
}

// --- FUNÇÕES DE ORDENAÇÃO E LÓGICA DIDÁTICA ---
int is_sorted(t_stack *a) {
    t_node *curr = a->head;
    if (!curr) return 1;
    while (curr->next) {
        if (curr->number > curr->next->number) return 0;
        curr = curr->next;
    }
    return 1;
}

int ft_sqrt(int nb) {
    int i = 1;
    if (nb <= 0) return (0);
    while (i * i <= nb) {
        if (i * i == nb) return (i);
        i++;
    }
    return (i - 1);
}

static void bubble_sort_array(int *arr, int size) {
    int i = 0, j, temp;
    while (i < size - 1) {
        j = i + 1;
        while (j < size) {
            if (arr[i] > arr[j]) {
                temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            }
            j++;
        }
        i++;
    }
}

int *get_sorted_array(t_stack *a) {
    int *ref = malloc(sizeof(int) * a->size);
    if (!ref) return NULL;
    t_node *curr = a->head;
    int i = 0;
    while (curr) { ref[i++] = curr->number; curr = curr->next; }
    bubble_sort_array(ref, a->size);
    return ref;
}

int get_max_val_in_b(t_stack *stack) {
    if (!stack || !stack->head) return -1;
    t_node *curr = stack->head;
    int max_val_b = curr->number;
    while (curr) {
        if (curr->number > max_val_b) max_val_b = curr->number;
        curr = curr->next;
    }
    return max_val_b;
}

int get_max_index_in_b(t_stack *stack) {
    if (!stack || !stack->head) return -1;
    t_node *curr = stack->head;
    int max_v = curr->number, max_idx = 0, curr_idx = 0;
    while (curr) {
        if (curr->number > max_v) { max_v = curr->number; max_idx = curr_idx; }
        curr = curr->next; curr_idx++;
    }
    return max_idx;
}

static int get_target_index(int *ref, t_stack *stack) {
    int target_index = 0;
    while (target_index < stack->size && ref[target_index] != stack->head->number)
        target_index++;
    return target_index;
}

static void k_sort_phase1(t_state *state, int *reference_array) {
    int chunk_size = ft_sqrt(state->a->size) * 1.4;
    if (chunk_size < 2) chunk_size = 2;
    int pushed_count = 0;

    set_explanation("Fase 1: Separação em Lotes", "INÍCIO FASE 1",
                    "Separando os números em 'lotes' de tamanhos parecidos.",
                    "Mover números parecidos para a Pilha B facilita a ordenação final.", -999999);

    while (state->a->size > 0 && !force_exit) {
        int val = state->a->head->number;
        int target_index = get_target_index(reference_array, state->a);

        if (target_index <= pushed_count) {
            set_explanation("Fase 1: Separação em Lotes", "pb + rb",
                            TextFormat("Moveu %d para B e enviou para o fundo de B.", val),
                            TextFormat("O %d é MUITO PEQUENO para o lote atual. Vai para a base da Pilha B.", val), val);
            pb(state);
            rb(state);
            pushed_count++;
        } else if (target_index <= pushed_count + chunk_size) {
            set_explanation("Fase 1: Separação em Lotes", "pb",
                            TextFormat("Moveu %d da Pilha A para a Pilha B.", val),
                            TextFormat("O %d pertence ao lote atual de números pequenos/médios.", val), val);
            pb(state);
            pushed_count++;
        } else {
            set_explanation("Fase 1: Separação em Lotes", "ra",
                            TextFormat("Girou a Pilha A (passou %d para o fundo).", val),
                            TextFormat("O %d é GRANDE DEMAIS para o lote atual. Giramos para procurar outro.", val), val);
            ra(state);
        }
    }
}

static void k_sort_phase2(t_state *state) {
    set_explanation("Fase 2: Reconstrução Ordenada", "INÍCIO FASE 2",
                    "A Pilha A está vazia! Devolvendo tudo de B para A em ordem exata.",
                    "Procuramos o MAIOR número restante em B para colocar no topo de A.", -999999);

    while (state->b->size > 0 && !force_exit) {
        int max_val_b = get_max_val_in_b(state->b);
        int highest_pos = get_max_index_in_b(state->b);

        set_explanation("Fase 2: Reconstrução Ordenada", "BUSCA",
                        TextFormat("Localizado o maior número em B: [%d]", max_val_b),
                        "Precisamos trazer esse número até o topo de B para enviá-lo a A.", max_val_b);

        if (highest_pos <= state->b->size / 2) {
            while (highest_pos > 0 && !force_exit) {
                set_explanation("Fase 2: Reconstrução Ordenada", "rb",
                                TextFormat("Girando B para cima para trazer %d ao topo.", max_val_b),
                                "Como está na metade superior, é mais rápido girar para CIMA.", max_val_b);
                rb(state);
                highest_pos--;
            }
        } else {
            int steps = state->b->size - highest_pos;
            while (steps > 0 && !force_exit) {
                set_explanation("Fase 2: Reconstrução Ordenada", "rrb",
                                TextFormat("Girando B para baixo para trazer %d ao topo.", max_val_b),
                                "Como está na metade inferior, é mais rápido girar para BAIXO.", max_val_b);
                rrb(state);
                steps--;
            }
        }

        if (!force_exit) {
            set_explanation("Fase 2: Reconstrução Ordenada", "pa",
                            TextFormat("Transferiu o maior número (%d) de B para A!", max_val_b),
                            "Como inserimos do maior para o menor, Pilha A fica montada em ordem crescente!", max_val_b);
            pa(state);
        }
    }
}

void medium_sort(t_state *state) {
    if (is_sorted(state->a)) {
        set_explanation("Concluído", "PRONTO", "A lista já veio totalmente ordenada!", "Nenhuma ação foi necessária.", -999999);
        return;
    }
    int *ref = get_sorted_array(state->a);
    if (!ref) return;

    k_sort_phase1(state, ref);
    if (!force_exit) k_sort_phase2(state);

    free(ref);
}

void *sort_thread_func(void *arg) {
    sleep(1);
    medium_sort(global_state);
    if (!force_exit) {
        sort_finished = true;
        set_explanation("CONCLUÍDO COM SUCESSO!", "FIM",
                        "Todos os números da Pilha A estão em ordem crescente!",
                        "Veja como as barras azuis formam uma rampa perfeita da esquerda para a direita.", -999999);
    }
    return NULL;
}

// --- CONTROLE DE EXECUÇÃO E REINÍCIO ---
void stop_sort_thread() {
    if (thread_running) {
        force_exit = true;
        pthread_join(sort_thread, NULL);
        thread_running = false;
    }
}

void reset_all() {
    stop_sort_thread();
    pthread_mutex_lock(&state_mutex);
    if (global_state) {
        clear_stack(global_state->a);
        clear_stack(global_state->b);
    }
    sort_finished = false;
    force_exit = false;
    is_paused = false;
    total_ops = 0;
    initial_disorder = 0.0f;
    active_target_val = -999999;
    strcpy(phase_name, "Menu Inicial");
    strcpy(action_name, "AGUARDANDO");
    strcpy(action_desc, "Configure os dados e clique em INICIAR.");
    strcpy(reason_desc, "Durante a ordenação, você poderá ver o motivo de cada movimento.");
    pthread_mutex_unlock(&state_mutex);
}

// --- UTILITÁRIOS VISUAIS E RENDERING ---
float calc_disorder(t_stack *a) {
    int out_of_order = 0, total_pairs = 0;
    t_node *curr = a->head;
    while (curr) {
        t_node *cmp = curr->next;
        while (cmp) {
            if (curr->number > cmp->number) out_of_order++;
            total_pairs++;
            cmp = cmp->next;
        }
        curr = curr->next;
    }
    return total_pairs == 0 ? 0 : ((float)out_of_order / total_pairs) * 100.0f;
}

void update_min_max(t_stack *a) {
    if (!a->head) return;
    min_val = a->head->number;
    max_val = a->head->number;
    t_node *curr = a->head;
    while (curr) {
        if (curr->number < min_val) min_val = curr->number;
        if (curr->number > max_val) max_val = curr->number;
        curr = curr->next;
    }
}

void generate_random_stack(t_stack *a, int n) {
    int *arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) arr[i] = i + 1;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
    }
    for (int i = n - 1; i >= 0; i--) {
        t_node *node = create_node(arr[i]);
        node->next = a->head;
        a->head = node;
        a->size++;
    }
    free(arr);
    update_min_max(a);
}

void parse_manual_input(t_stack *a, const char *str) {
    int *temp = malloc(sizeof(int) * 4096);
    int count = 0;
    char buf[4096];
    strcpy(buf, str);
    char *tok = strtok(buf, " ,");
    while (tok != NULL) {
        temp[count++] = atoi(tok);
        tok = strtok(NULL, " ,");
    }
    max_elements = count > 0 ? count : 1;
    for (int i = count - 1; i >= 0; i--) {
        t_node *node = create_node(temp[i]);
        node->next = a->head;
        a->head = node;
        a->size++;
    }
    free(temp);
    update_min_max(a);
}

void draw_stack(t_stack *stack, int start_x, int width, int height, Color base_color, const char *label) {
    int stack_h = height - 320;
    DrawRectangleLinesEx((Rectangle){start_x - 5, 230, width + 10, stack_h}, 2, LIGHTGRAY);
    DrawText(label, start_x + (width / 2) - 100, 205, 20, base_color);

    if (!stack || stack->size == 0) {
        DrawText("PILHA VAZIA", start_x + (width / 2) - 60, 230 + (stack_h / 2), 20, LIGHTGRAY);
        return;
    }

    float bar_width = (float)width / max_elements;
    float range = (max_val - min_val) == 0 ? 1 : (max_val - min_val);

    t_node *curr = stack->head;
    int i = 0;
    while (curr) {
        float normalized = (float)(curr->number - min_val) / range;
        float bar_height = (normalized * (stack_h - 40)) + 15;

        Color bar_color = base_color;
        if (curr->number == active_target_val) {
            bar_color = GOLD;
        } else if (i == 0) {
            bar_color = ORANGE;
        }

        float posX = start_x + (i * bar_width);
        float posY = (230 + stack_h) - bar_height - 10;

        DrawRectangle(posX, posY, bar_width > 2 ? bar_width - 1 : 1, bar_height, bar_color);

        if (max_elements <= 80 && bar_width >= 12) {
            DrawText(TextFormat("%d", curr->number), posX + (bar_width / 2) - 6, posY - 18, 14, DARKGRAY);
        }

        curr = curr->next;
        i++;
    }
}

// Auxiliar de UI para Caixa de Texto Editável
void DrawTextBox(Rectangle rect, char *buffer, FieldID field_id, const char *label) {
    bool is_active = (active_field == field_id);
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, rect)) {
            active_field = field_id;
        }
    }

    DrawRectangleRec(rect, is_active ? WHITE : LIGHTGRAY);
    DrawRectangleLinesEx(rect, is_active ? 2 : 1, is_active ? BLUE : DARKGRAY);
    DrawText(buffer, rect.x + 10, rect.y + (rect.height / 2) - 9, 18, DARKBLUE);

    if (label) {
        DrawText(label, rect.x, rect.y - 22, 16, BLACK);
    }

    if (is_active && ((int)(GetTime() * 2) % 2 == 0)) {
        int text_w = MeasureText(buffer, 18);
        DrawText("|", rect.x + 12 + text_w, rect.y + (rect.height / 2) - 10, 20, BLUE);
    }
}

bool DrawButton(Rectangle bounds, const char *text, Color baseColor, Color textColor) {
    bool clicked = false;
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, bounds)) {
        DrawRectangleRec(bounds, LIGHTGRAY);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) clicked = true;
    } else {
        DrawRectangleRec(bounds, baseColor);
    }
    DrawRectangleLinesEx(bounds, 2, BLACK);
    int text_width = MeasureText(text, 18);
    DrawText(text, bounds.x + (bounds.width / 2) - (text_width / 2), bounds.y + (bounds.height / 2) - 9, 18, textColor);
    return clicked;
}

// --- FUNÇÃO PRINCIPAL ---
int main(void) {
    srand(time(NULL));

    global_state = malloc(sizeof(t_state));
    global_state->a = malloc(sizeof(t_stack));
    global_state->b = malloc(sizeof(t_stack));
    global_state->a->head = NULL; global_state->a->size = 0;
    global_state->b->head = NULL; global_state->b->size = 0;

    // Inicialização padrão Full HD
    InitWindow(window_width, window_height, "Push_Swap - Visualizador Didático");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Gerenciamento de Entrada de Texto no Menu
        if (current_state == MENU && active_field != FIELD_NONE) {
            char *buf = NULL;
            int max_l = 32;

            if (active_field == FIELD_MANUAL_SEQ) { buf = input_buffer; max_l = 4000; }
            else if (active_field == FIELD_RES) { buf = res_buffer; max_l = 25; }
            else if (active_field == FIELD_SPEED) { buf = speed_buffer; max_l = 10; }
            else if (active_field == FIELD_STEPS) { buf = steps_buffer; max_l = 10; }
            else if (active_field == FIELD_RANDOM_COUNT) { buf = random_count_buffer; max_l = 10; }

            if (buf) {
                int key = GetCharPressed();
                while (key > 0) {
                    int len = strlen(buf);
                    if (len < max_l - 1) {
                        bool valid = false;
                        if (active_field == FIELD_MANUAL_SEQ) {
                            valid = (key >= '0' && key <= '9') || key == ' ' || key == '-' || key == ',';
                        } else if (active_field == FIELD_RES) {
                            valid = (key >= '0' && key <= '9') || key == 'x' || key == 'X' || key == ' ';
                        } else {
                            valid = (key >= '0' && key <= '9');
                        }

                        if (valid) {
                            buf[len] = (char)key;
                            buf[len + 1] = '\0';
                        }
                    }
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    int len = strlen(buf);
                    if (len > 0) buf[len - 1] = '\0';
                }

                // Atalho: Pressionar ENTER aplica a resolução imediatamente se o campo de resolução estiver em foco
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
                    if (active_field == FIELD_RES) {
                        apply_resolution_and_mode();
                    }
                    active_field = FIELD_NONE;
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (current_state == MENU) {
            int centerX = window_width / 2;

            DrawText("MENU DE CONFIGURAÇÃO DO VISUALIZADOR", centerX - 260, 40, 28, DARKBLUE);

            // 1. Configuração de Tela e Resolução
            DrawText("1. Configurações de Tela:", 60, 110, 22, BLACK);
            
            // Alternar Modo (Janela / Tela Cheia) com aplicação imediata
            if (DrawButton((Rectangle){60, 140, 150, 35}, "Modo: JANELA", !is_fullscreen ? SKYBLUE : RAYWHITE, BLACK)) {
                is_fullscreen = false;
                apply_resolution_and_mode();
            }
            if (DrawButton((Rectangle){220, 140, 160, 35}, "Modo: TELA CHEIA", is_fullscreen ? SKYBLUE : RAYWHITE, BLACK)) {
                is_fullscreen = true;
                apply_resolution_and_mode();
            }

            // Entrada Manual de Resolução + BOTÃO APLICAR
            DrawTextBox((Rectangle){60, 200, 180, 35}, res_buffer, FIELD_RES, "Resolução (YYYY x ZZZZ):");
            if (DrawButton((Rectangle){250, 200, 110, 35}, "APLICAR", GREEN, WHITE)) {
                apply_resolution_and_mode();
            }

            // Presets Rápidos de Resolução (Com aplicação imediata ao clicar)
            DrawText("Atalhos:", 380, 180, 16, DARKGRAY);
            if (DrawButton((Rectangle){380, 200, 110, 35}, "1920x1080", RAYWHITE, BLACK)) {
                strcpy(res_buffer, "1920 x 1080");
                apply_resolution_and_mode();
            }
            if (DrawButton((Rectangle){500, 200, 110, 35}, "1280x720", RAYWHITE, BLACK)) {
                strcpy(res_buffer, "1280 x 720");
                apply_resolution_and_mode();
            }
            if (DrawButton((Rectangle){620, 200, 110, 35}, "800x600", RAYWHITE, BLACK)) {
                strcpy(res_buffer, "800 x 600");
                apply_resolution_and_mode();
            }

            // 2. Velocidade e Número de Passos (Com espaçamento corrigido)
            DrawText("2. Execução & Animação:", 60, 260, 22, BLACK);
            
            // Caixa 1: Aumentamos o Y para 315 (Label fica em Y = 293, logo abaixo do título)
            DrawTextBox((Rectangle){60, 315, 240, 35}, speed_buffer, FIELD_SPEED, "Velocidade por movimento (ms):");
            
            // Caixa 2: Movemos o X para 340 para não encostar na caixa 1
            DrawTextBox((Rectangle){340, 315, 240, 35}, steps_buffer, FIELD_STEPS, "Número de Passos por ciclo:");

            // 3. Sequência de Dados
            DrawText("3. Origem dos Dados:", 60, 365, 22, BLACK);
            if (DrawButton((Rectangle){60, 395, 180, 35}, "Aleatório", !manual_input_mode ? SKYBLUE : RAYWHITE, BLACK)) manual_input_mode = false;
            if (DrawButton((Rectangle){250, 395, 180, 35}, "Entrada Manual", manual_input_mode ? SKYBLUE : RAYWHITE, BLACK)) manual_input_mode = true;

            if (!manual_input_mode) {
                DrawTextBox((Rectangle){60, 460, 220, 35}, random_count_buffer, FIELD_RANDOM_COUNT, "Quantidade de Números:");
            } else {
                DrawTextBox((Rectangle){60, 460, window_width - 120, 35}, input_buffer, FIELD_MANUAL_SEQ, "Sequência de Dígitos (separados por espaço):");
            }

            // BOTÃO INICIAR
            if (DrawButton((Rectangle){centerX - 150, window_height - 90, 300, 50}, "INICIAR ORDENAÇÃO", GREEN, WHITE)) {
                apply_resolution_and_mode();
                reset_all();

                int speed_ms = atoi(speed_buffer);
                delay_us = speed_ms * 1000;

                steps_per_batch = atoi(steps_buffer);
                if (steps_per_batch < 1) steps_per_batch = 1;

                if (manual_input_mode && strlen(input_buffer) > 0) {
                    parse_manual_input(global_state->a, input_buffer);
                } else {
                    max_elements = atoi(random_count_buffer);
                    if (max_elements < 2) max_elements = 2;
                    generate_random_stack(global_state->a, max_elements);
                }

                initial_disorder = calc_disorder(global_state->a);
                current_state = SORTING;

                pthread_create(&sort_thread, NULL, sort_thread_func, NULL);
                thread_running = true;
            }
        } 
        else if (current_state == SORTING) {
            if (IsKeyPressed(KEY_UP)) delay_us = delay_us >= 5000 ? delay_us - 5000 : 0;
            if (IsKeyPressed(KEY_DOWN)) delay_us += 5000;
            if (IsKeyPressed(KEY_SPACE)) is_paused = !is_paused;
            if (IsKeyPressed(KEY_R)) {
                reset_all();
                current_state = MENU;
            }

            pthread_mutex_lock(&state_mutex);

            // PAINEL DIDÁTICO SUPERIOR
            DrawRectangle(20, 15, window_width - 40, 170, WHITE);
            DrawRectangleLinesEx((Rectangle){20, 15, (float)window_width - 40, 170}, 2, DARKBLUE);

            if (DrawButton((Rectangle){window_width - 250, 25, 210, 35}, "< MENU / RECOMEÇAR [R]", RED, WHITE)) {
                pthread_mutex_unlock(&state_mutex);
                reset_all();
                current_state = MENU;
                EndDrawing();
                continue;
            }

            if (DrawButton((Rectangle){window_width - 450, 25, 190, 35}, is_paused ? "CONTINUAR [ESPAÇO]" : "PAUSAR [ESPAÇO]", is_paused ? GREEN : ORANGE, WHITE)) {
                is_paused = !is_paused;
            }

            DrawText(TextFormat("FASE ATUAL: %s", phase_name), 35, 25, 22, DARKBLUE);
            DrawText(TextFormat("Comando: %s", action_name), 35, 55, 20, PURPLE);

            DrawRectangle(35, 85, window_width/2 - 50, 85, LIGHTGRAY);
            DrawText("O QUE ESTÁ ACONTECENDO?", 45, 90, 14, DARKBLUE);
            DrawText(action_desc, 45, 110, 15, BLACK);

            DrawRectangle(window_width/2, 85, window_width/2 - 35, 85, LIGHTGRAY);
            DrawText("POR QUE O ALGORITMO FAZ ISSO?", window_width/2 + 10, 90, 14, DARKGREEN);
            DrawText(reason_desc, window_width/2 + 10, 110, 15, BLACK);

            // PILHAS DE DADOS
            int stack_w = (window_width - 150) / 2;
            draw_stack(global_state->a, 50, stack_w, window_height, DARKBLUE, "Pilha A (Entrada e Resultado)");
            draw_stack(global_state->b, 100 + stack_w, stack_w, window_height, MAROON, "Pilha B (Auxiliar de Trabalho)");

            // RODAPÉ COM ESTATÍSTICAS
            DrawText(TextFormat("Total de Operações: %d", total_ops), 50, window_height - 35, 18, BLACK);
            DrawText(TextFormat("Velocidade: %d ms | Passos por ciclo: %d", delay_us / 1000, steps_per_batch), 350, window_height - 35, 18, DARKGRAY);

            if (is_paused && !sort_finished) {
                DrawText("|| PAUSADO - Leia a explicação acima e pressione ESPAÇO para continuar", window_width/2 - 320, window_height - 70, 18, RED);
            }

            pthread_mutex_unlock(&state_mutex);
        }

        EndDrawing();
    }

    reset_all();
    CloseWindow();
    return 0;
}

// gcc visualizer.c -o visualizer -lraylib -lGL -lm -lpthread -ldl -lrt -lX11