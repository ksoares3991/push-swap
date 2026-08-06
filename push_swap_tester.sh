#!/usr/bin/env bash

# Push_swap tester - strategies, parser, benchmark and performance.
# Usage:
#   ./push_swap_tester.sh [path/to/push_swap] [path/to/checker]
# Examples:
#   ./push_swap_tester.sh
#   ./push_swap_tester.sh ./push_swap ./checker_linux
# Environment:
#   RUNS_100=3 RUNS_500=2 NO_COLOR=1 ./push_swap_tester.sh

set -uo pipefail

PUSH_SWAP=${1:-./push_swap}
CHECKER=${2:-${CHECKER:-}}
RUNS_100=${RUNS_100:-3}
RUNS_500=${RUNS_500:-2}

if [[ -z "$CHECKER" ]]; then
    for candidate in ./checker_linux ./checker ./checker_Mac; do
        if [[ -x "$candidate" ]]; then
            CHECKER=$candidate
            break
        fi
    done
fi

if [[ -t 1 && -z "${NO_COLOR:-}" ]]; then
    RESET='\033[0m'
    BOLD='\033[1m'
    DIM='\033[2m'
    RED='\033[31m'
    GREEN='\033[32m'
    YELLOW='\033[33m'
    BLUE='\033[34m'
    MAGENTA='\033[35m'
    CYAN='\033[36m'
    WHITE='\033[97m'
else
    RESET=''
    BOLD=''
    DIM=''
    RED=''
    GREEN=''
    YELLOW=''
    BLUE=''
    MAGENTA=''
    CYAN=''
    WHITE=''
fi

PASS_COUNT=0
FAIL_COUNT=0
WARN_COUNT=0
TEST_COUNT=0
SECTION_COUNT=0

TMP_DIR=$(mktemp -d 2>/dev/null || mktemp -d -t push_swap_tester)
REPORT="push_swap_test_inputs_$(date +%Y%m%d_%H%M%S).txt"
MAIN_BASHPID=${BASHPID:-$$}

cleanup() {
    if [[ ${BASHPID:-$$} == "$MAIN_BASHPID" ]]; then
        rm -rf "$TMP_DIR"
    fi
}

trap cleanup EXIT
trap 'cleanup; exit 130' INT
trap 'cleanup; exit 143' TERM

printf 'Push_swap randomized test inputs\nGenerated: %s\nPush_swap: %s\nChecker: %s\n\n' \
    "$(date '+%Y-%m-%d %H:%M:%S')" "$PUSH_SWAP" "${CHECKER:-not found}" > "$REPORT"

repeat_char() {
    local char=$1 count=$2
    printf '%*s' "$count" '' | tr ' ' "$char"
}

banner() {
    printf '\n%b' "$CYAN$BOLD"
    repeat_char '=' 76
    printf '\n  PUSH_SWAP TESTER - RANDOMIZADO, COMPLETO E COMPARATIVO\n'
    repeat_char '=' 76
    printf '%b\n' "$RESET"
    printf '%bExecutável:%b %s\n' "$BOLD" "$RESET" "$PUSH_SWAP"
    printf '%bChecker:%b    %s\n' "$BOLD" "$RESET" "${CHECKER:-não encontrado}"
    printf '%bEntradas:%b   %s\n\n' "$BOLD" "$RESET" "$REPORT"
}

section() {
    SECTION_COUNT=$((SECTION_COUNT + 1))
    printf '\n%b[%02d] %s%b\n' "$MAGENTA$BOLD" "$SECTION_COUNT" "$1" "$RESET"
    printf '%b' "$MAGENTA"
    repeat_char '-' 76
    printf '%b\n' "$RESET"
}

case_header() {
    TEST_COUNT=$((TEST_COUNT + 1))
    printf '\n%bTeste %02d:%b %s\n' "$BLUE$BOLD" "$TEST_COUNT" "$RESET" "$1"
}

expected() {
    printf '  %bEsperado:%b %s\n' "$CYAN$BOLD" "$RESET" "$1"
}

obtained() {
    printf '  %bObtido:%b   %s\n' "$WHITE$BOLD" "$RESET" "$1"
}

pass() {
    PASS_COUNT=$((PASS_COUNT + 1))
    printf '  %b✓ PASSOU%b %s\n' "$GREEN$BOLD" "$RESET" "${1:-}"
}

fail() {
    FAIL_COUNT=$((FAIL_COUNT + 1))
    printf '  %b✗ FALHOU%b %s\n' "$RED$BOLD" "$RESET" "${1:-}"
}

warn() {
    WARN_COUNT=$((WARN_COUNT + 1))
    printf '  %b! AVISO%b  %s\n' "$YELLOW$BOLD" "$RESET" "${1:-}"
}

record_input() {
    local label=$1
    shift
    {
        printf '[%s]\n' "$label"
        printf '%s\n\n' "$*"
    } >> "$REPORT"
}

preview_array() {
    local -a data=("$@")
    local size=${#data[@]}
    local limit=14
    local i

    if (( size <= limit )); then
        printf '%s' "${data[*]}"
        return
    fi
    for ((i = 0; i < limit; i++)); do
        printf '%s ' "${data[i]}"
    done
    printf '... (%d números; lista completa em %s)' "$size" "$REPORT"
}

require_tools() {
    local missing=0

    if [[ ! -x "$PUSH_SWAP" ]]; then
        printf '%bErro:%b push_swap não encontrado ou sem permissão de execução: %s\n' \
            "$RED$BOLD" "$RESET" "$PUSH_SWAP"
        missing=1
    fi
    if [[ -z "${CHECKER:-}" || ! -x "$CHECKER" ]]; then
        printf '%bErro:%b checker não encontrado. Informe o caminho como segundo argumento.\n' \
            "$RED$BOLD" "$RESET"
        printf 'Exemplo: %s ./push_swap ./checker_linux\n' "$0"
        missing=1
    fi
    if ! command -v shuf >/dev/null 2>&1 && ! command -v python3 >/dev/null 2>&1; then
        printf '%bErro:%b é necessário ter shuf ou python3 para gerar entradas aleatórias.\n' \
            "$RED$BOLD" "$RESET"
        missing=1
    fi
    (( missing == 0 )) || exit 2
}

gen_unique() {
    local count=$1 min=$2 max=$3

    if command -v shuf >/dev/null 2>&1; then
        shuf -i "${min}-${max}" -n "$count"
    else
        python3 - "$count" "$min" "$max" <<'PY'
import random
import sys

count, minimum, maximum = map(int, sys.argv[1:])
for value in random.sample(range(minimum, maximum + 1), count):
    print(value)
PY
    fi
}

shuffle_lines() {
    if command -v shuf >/dev/null 2>&1; then
        shuf
    else
        python3 -c 'import random,sys; x=sys.stdin.read().splitlines(); random.shuffle(x); print("\\n".join(x))'
    fi
}

sort_numeric_lines() {
    sort -n
}

file_is_empty() {
    [[ ! -s "$1" ]]
}

file_is_exact_error() {
    local expected_file="$TMP_DIR/expected_error"
    printf 'Error\n' > "$expected_file"
    cmp -s "$1" "$expected_file"
}

file_display() {
    local file=$1 prefix=${2:-}
    local line count=0

    if [[ ! -s "$file" ]]; then
        printf '%s<vazio>' "$prefix"
        return
    fi
    while IFS= read -r line || [[ -n "$line" ]]; do
        if (( count > 0 )); then
            printf ' | '
        fi
        printf '%s%s\\n' "$prefix" "$line"
        count=$((count + 1))
        if (( count == 8 )); then
            local remaining
            remaining=$(awk 'END {print NR}' "$file")
            if (( remaining > count )); then
                printf ' | ... +%d linha(s)' "$((remaining - count))"
            fi
            break
        fi
    done < "$file"
}

operation_count() {
    awk 'END {print NR + 0}' "$1"
}

valid_operation_stream() {
    local file=$1
    awk '
        !/^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$/ { bad = 1 }
        END { exit bad }
    ' "$file"
}

has_final_newline_if_nonempty() {
    local file=$1
    local last_byte

    [[ ! -s "$file" ]] && return 0
    last_byte=$(tail -c 1 "$file" | od -An -t u1 | tr -d '[:space:]')
    [[ "$last_byte" == "10" ]]
}

run_capture() {
    local out=$1 err=$2
    shift 2
    "$@" > "$out" 2> "$err"
    return $?
}

checker_for_file() {
    local operations=$1 checker_out=$2 checker_err=$3
    shift 3
    "$CHECKER" "$@" < "$operations" > "$checker_out" 2> "$checker_err"
    return $?
}

checker_text() {
    tr -d '\r\n' < "$1"
}

classify_3() {
    local count=$1
    if (( count <= 3 )); then
        printf 'bom (≤3)'
    elif (( count <= 5 )); then
        printf 'aceitável (≤5)'
    else
        printf 'acima do razoável (>5)'
    fi
}

classify_5() {
    local count=$1
    if (( count <= 12 )); then
        printf 'bom (≤12)'
    elif (( count <= 15 )); then
        printf 'aceitável (≤15)'
    else
        printf 'acima do razoável (>15)'
    fi
}

classify_100() {
    local count=$1
    if (( count < 700 )); then
        printf 'excelente (<700)'
    elif (( count < 1500 )); then
        printf 'bom (<1500)'
    elif (( count < 2000 )); then
        printf 'aprovado (<2000)'
    else
        printf 'reprovado (precisa ser <2000)'
    fi
}

classify_500() {
    local count=$1
    if (( count < 5500 )); then
        printf 'excelente (<5500)'
    elif (( count < 8000 )); then
        printf 'bom (<8000)'
    elif (( count < 12000 )); then
        printf 'aprovado (<12000)'
    else
        printf 'reprovado (precisa ser <12000)'
    fi
}

run_error_case() {
    local title=$1
    shift
    local out="$TMP_DIR/error_${TEST_COUNT}_out"
    local err="$TMP_DIR/error_${TEST_COUNT}_err"
    local status

    case_header "$title"
    printf '  %bComando:%b  %q' "$DIM" "$RESET" "$PUSH_SWAP"
    printf ' %q' "$@"
    printf '\n'
    expected 'stdout vazio; stderr exatamente "Error\\n".'

    run_capture "$out" "$err" "$PUSH_SWAP" "$@"
    status=$?

    printf '  %bObtido:%b   stdout=' "$WHITE$BOLD" "$RESET"
    file_display "$out"
    printf '; stderr='
    file_display "$err"
    printf '; status=%d\n' "$status"

    if file_is_empty "$out" && file_is_exact_error "$err"; then
        pass
    else
        fail 'A mensagem precisa estar somente no stderr e ser exatamente Error seguido de newline.'
    fi
}

run_silent_case() {
    local title=$1
    shift
    local out="$TMP_DIR/silent_${TEST_COUNT}_out"
    local err="$TMP_DIR/silent_${TEST_COUNT}_err"
    local status

    case_header "$title"
    expected 'nenhuma saída em stdout ou stderr.'
    run_capture "$out" "$err" "$PUSH_SWAP" "$@"
    status=$?

    printf '  %bObtido:%b   stdout=' "$WHITE$BOLD" "$RESET"
    file_display "$out"
    printf '; stderr='
    file_display "$err"
    printf '; status=%d\n' "$status"

    if file_is_empty "$out" && file_is_empty "$err"; then
        pass
    else
        fail 'Uma entrada já ordenada, ou a ausência de argumentos, não deve imprimir nada.'
    fi
}

run_valid_sort_case() {
    local title=$1 strategy=$2 performance_kind=${3:-none}
    shift 3
    local -a numbers=("$@")
    local out="$TMP_DIR/sort_${TEST_COUNT}_out"
    local err="$TMP_DIR/sort_${TEST_COUNT}_err"
    local checker_out="$TMP_DIR/sort_${TEST_COUNT}_checker_out"
    local checker_err="$TMP_DIR/sort_${TEST_COUNT}_checker_err"
    local -a cmd=("$PUSH_SWAP")
    local status checker_status result count stream_ok newline_ok

    [[ -n "$strategy" ]] && cmd+=("$strategy")
    cmd+=("${numbers[@]}")

    case_header "$title"
    printf '  %bEntrada:%b  ' "$DIM" "$RESET"
    preview_array "${numbers[@]}"
    printf '\n'
    expected 'checker = OK; operações válidas; stderr vazio.'

    run_capture "$out" "$err" "${cmd[@]}"
    status=$?
    checker_for_file "$out" "$checker_out" "$checker_err" "${numbers[@]}"
    checker_status=$?
    result=$(checker_text "$checker_out")
    count=$(operation_count "$out")

    valid_operation_stream "$out"
    stream_ok=$?
    has_final_newline_if_nonempty "$out"
    newline_ok=$?

    obtained "checker=${result:-<vazio>}; operações=$count; push_swap status=$status; checker status=$checker_status; stderr=$(file_display "$err")"

    if [[ "$result" == 'OK' ]] && file_is_empty "$err" && file_is_empty "$checker_err" \
        && (( stream_ok == 0 )) && (( newline_ok == 0 )); then
        case "$performance_kind" in
            3)
                if (( count <= 5 )); then pass "$(classify_3 "$count")"; else warn "Ordenou, mas usou $count operações: $(classify_3 "$count")."; fi
                ;;
            5)
                if (( count <= 15 )); then pass "$(classify_5 "$count")"; else warn "Ordenou, mas usou $count operações: $(classify_5 "$count")."; fi
                ;;
            100)
                if (( count < 2000 )); then pass "$(classify_100 "$count")"; else fail "Ordenou, porém excedeu o limite: $(classify_100 "$count")."; fi
                ;;
            500)
                if (( count < 12000 )); then pass "$(classify_500 "$count")"; else fail "Ordenou, porém excedeu o limite: $(classify_500 "$count")."; fi
                ;;
            *) pass ;;
        esac
    else
        fail 'A sequência não foi validada pelo checker, contém operação inválida, falta newline final ou houve saída indevida.'
        if [[ -s "$checker_err" ]]; then
            printf '  %bChecker stderr:%b ' "$RED" "$RESET"
            file_display "$checker_err"
            printf '\n'
        fi
    fi

    LAST_OPERATION_COUNT=$count
    LAST_OUTPUT_FILE=$out
    LAST_CHECKER_RESULT=$result
}

extract_disorder_percent() {
    local file=$1
    awk '
        tolower($0) ~ /disorder/ {
            line = $0
            gsub(",", ".", line)
            if (match(line, /[0-9]+([.][0-9]+)?[[:space:]]*%/)) {
                value = substr(line, RSTART, RLENGTH)
                gsub(/[[:space:]%]/, "", value)
                print value
                exit
            }
        }
    ' "$file"
}

percent_close_to_zero() {
    awk -v value="$1" 'BEGIN { exit !(value >= 0 && value <= 0.10) }'
}

percent_close_to_hundred() {
    awk -v value="$1" 'BEGIN { exit !(value >= 99.90 && value <= 100.10) }'
}

benchmark_has_field() {
    local file=$1 regex=$2
    grep -Eiq "$regex" "$file"
}

benchmark_has_operation_counts() {
    local file=$1 op
    for op in sa sb ss pa pb ra rb rr rra rrb rrr; do
        if ! grep -Eiq "(^|[^[:alnum:]_])${op}([^[:alnum:]_]|$)[^0-9-]*[0-9]+" "$file"; then
            return 1
        fi
    done
    return 0
}

run_benchmark_structure_case() {
    local -a numbers=("$@")
    local out="$TMP_DIR/bench_structure_out"
    local err="$TMP_DIR/bench_structure_err"
    local checker_out="$TMP_DIR/bench_structure_checker_out"
    local checker_err="$TMP_DIR/bench_structure_checker_err"
    local result count status checker_status
    local missing=()

    case_header 'Benchmark: separação stdout/stderr e campos obrigatórios'
    printf '  %bEntrada:%b  --bench --simple ' "$DIM" "$RESET"
    preview_array "${numbers[@]}"
    printf '\n'
    expected 'stdout contém somente operações válidas; stderr contém disorder, estratégia, complexidade, total e contagem das 11 operações.'

    run_capture "$out" "$err" "$PUSH_SWAP" --bench --simple "${numbers[@]}"
    status=$?
    checker_for_file "$out" "$checker_out" "$checker_err" "${numbers[@]}"
    checker_status=$?
    result=$(checker_text "$checker_out")
    count=$(operation_count "$out")

    benchmark_has_field "$err" 'disorder' || missing+=('disorder')
    benchmark_has_field "$err" 'strategy|estrat[eé]gia|simple' || missing+=('strategy')
    benchmark_has_field "$err" 'O[[:space:]]*\(' || missing+=('complexity O(...)')
    benchmark_has_field "$err" 'total_ops|total[^[:cntrl:]]*operation|operation[^[:cntrl:]]*total|total[^[:cntrl:]]*opera' || missing+=('total operations')
    benchmark_has_operation_counts "$err" || missing+=('individual operation counts')

    obtained "checker=${result:-<vazio>}; stdout=$count operação(ões); stderr=$(file_display "$err")"

    if [[ "$result" == 'OK' ]] && (( ${#missing[@]} == 0 )) \
        && valid_operation_stream "$out" && file_is_empty "$checker_err"; then
        pass
    else
        fail "Campos ausentes ou validação incorreta: ${missing[*]:-nenhum campo identificado como ausente}."
    fi
    printf '  %bDetalhe:%b push_swap status=%d; checker status=%d\n' "$DIM" "$RESET" "$status" "$checker_status"
}

run_disorder_case() {
    local title=$1 expectation=$2
    shift 2
    local -a numbers=("$@")
    local out="$TMP_DIR/disorder_${TEST_COUNT}_out"
    local err="$TMP_DIR/disorder_${TEST_COUNT}_err"
    local percent status

    case_header "$title"
    printf '  %bEntrada:%b  ' "$DIM" "$RESET"
    preview_array "${numbers[@]}"
    printf '\n'
    if [[ "$expectation" == zero ]]; then
        expected 'disorder próximo de 0,00%.'
    else
        expected 'disorder próximo de 100,00%.'
    fi

    run_capture "$out" "$err" "$PUSH_SWAP" --bench --adaptive "${numbers[@]}"
    status=$?
    percent=$(extract_disorder_percent "$err")
    obtained "disorder=${percent:-não encontrado}%; status=$status; benchmark=$(file_display "$err")"

    if [[ -z "$percent" ]]; then
        fail 'Não foi possível encontrar uma porcentagem na linha de disorder do stderr.'
    elif [[ "$expectation" == zero ]] && percent_close_to_zero "$percent"; then
        pass
    elif [[ "$expectation" == hundred ]] && percent_close_to_hundred "$percent"; then
        pass
    else
        fail "Porcentagem fora do esperado: ${percent}%."
    fi
}

run_default_adaptive_case() {
    local -a numbers=("$@")
    local default_out="$TMP_DIR/default_adaptive_default_out"
    local default_err="$TMP_DIR/default_adaptive_default_err"
    local adaptive_out="$TMP_DIR/default_adaptive_explicit_out"
    local adaptive_err="$TMP_DIR/default_adaptive_explicit_err"
    local checker_default_out="$TMP_DIR/default_adaptive_checker_default_out"
    local checker_default_err="$TMP_DIR/default_adaptive_checker_default_err"
    local checker_adaptive_out="$TMP_DIR/default_adaptive_checker_explicit_out"
    local checker_adaptive_err="$TMP_DIR/default_adaptive_checker_explicit_err"
    local default_result adaptive_result same_stream='não'

    case_header 'Sem flag deve usar o comportamento de --adaptive'
    printf '  %bEntrada:%b  ' "$DIM" "$RESET"
    preview_array "${numbers[@]}"
    printf '\n'
    expected 'as duas execuções ordenam; idealmente produzem a mesma sequência determinística.'

    run_capture "$default_out" "$default_err" "$PUSH_SWAP" "${numbers[@]}"
    run_capture "$adaptive_out" "$adaptive_err" "$PUSH_SWAP" --adaptive "${numbers[@]}"
    checker_for_file "$default_out" "$checker_default_out" "$checker_default_err" "${numbers[@]}"
    checker_for_file "$adaptive_out" "$checker_adaptive_out" "$checker_adaptive_err" "${numbers[@]}"
    default_result=$(checker_text "$checker_default_out")
    adaptive_result=$(checker_text "$checker_adaptive_out")
    cmp -s "$default_out" "$adaptive_out" && same_stream='sim'

    obtained "default=$default_result/$(operation_count "$default_out") ops; --adaptive=$adaptive_result/$(operation_count "$adaptive_out") ops; sequências iguais=$same_stream"

    if [[ "$default_result" == 'OK' && "$adaptive_result" == 'OK' ]] \
        && file_is_empty "$default_err" && file_is_empty "$adaptive_err"; then
        if [[ "$same_stream" == sim ]]; then
            pass
        else
            warn 'Ambas ordenam, mas as sequências diferem. Confirme no código se o caminho padrão chama realmente a estratégia adaptive.'
        fi
    else
        fail 'O modo padrão e/ou --adaptive não ordenou corretamente.'
    fi
}

banner
require_tools

section 'Validação de argumentos e gerenciamento de erros'

mapfile -t parser_values < <(gen_unique 4 10 900)
non_numeric="texto_$((RANDOM + 100))"
run_error_case 'Parâmetro não numérico' "${parser_values[0]}" "$non_numeric" "${parser_values[1]}"

mapfile -t duplicate_values < <(gen_unique 3 100 900)
run_error_case 'Número duplicado' "${duplicate_values[0]}" "${duplicate_values[1]}" "${duplicate_values[0]}" "${duplicate_values[2]}"

overflow_value=$((2147483648 + RANDOM))
run_error_case 'Número maior que INT_MAX' "${parser_values[2]}" "$overflow_value" "${parser_values[3]}"

run_silent_case 'Execução sem parâmetros'

section 'Seletores de estratégia e comportamento padrão'

mapfile -t flag_sorted < <(gen_unique 5 20 800 | sort_numeric_lines)
flag_reverse=()
for ((i=${#flag_sorted[@]}-1; i>=0; i--)); do flag_reverse+=("${flag_sorted[i]}"); done
record_input 'strategies_reverse_5' "${flag_reverse[@]}"

for strategy in --simple --medium --complex --adaptive; do
    run_valid_sort_case "Estratégia $strategy com 5 números em ordem reversa" "$strategy" none "${flag_reverse[@]}"
done
run_default_adaptive_case "${flag_reverse[@]}"

section 'Entradas já ordenadas: nenhuma instrução deve ser impressa'

mapfile -t sorted_10 < <(gen_unique 10 0 500 | sort_numeric_lines)
record_input 'already_sorted_10' "${sorted_10[@]}"
run_silent_case 'Um único número' "${sorted_10[0]}"
run_silent_case 'Dois números em ordem crescente' "${sorted_10[0]}" "${sorted_10[1]}"
run_silent_case 'Quatro números em ordem crescente' "${sorted_10[@]:0:4}"
run_silent_case 'Dez números em ordem crescente' "${sorted_10[@]}"

section 'Todas as combinações de 3 números aleatórios'

mapfile -t base_3 < <(gen_unique 3 0 999 | sort_numeric_lines)
a=${base_3[0]}; b=${base_3[1]}; c=${base_3[2]}
permutations_3=(
    "$a $b $c"
    "$a $c $b"
    "$b $a $c"
    "$b $c $a"
    "$c $a $b"
    "$c $b $a"
)
for idx in "${!permutations_3[@]}"; do
    read -r -a current <<< "${permutations_3[idx]}"
    record_input "three_numbers_permutation_$((idx + 1))" "${current[@]}"
    run_valid_sort_case "Permutação $((idx + 1))/6 de 3 números" '' 3 "${current[@]}"
done

section 'Três conjuntos aleatórios de 5 números'

for run in 1 2 3; do
    mapfile -t values_5 < <(gen_unique 5 1 999 | shuffle_lines)
    record_input "five_numbers_run_$run" "${values_5[@]}"
    run_valid_sort_case "Conjunto aleatório $run/3 com 5 números" '' 5 "${values_5[@]}"
done

section 'Modo --bench: canal correto, conteúdo e cálculo de disorder'

mapfile -t bench_base < <(gen_unique 5 50 950 | sort_numeric_lines)
bench_reverse=()
for ((i=${#bench_base[@]}-1; i>=0; i--)); do bench_reverse+=("${bench_base[i]}"); done
record_input 'benchmark_reverse_5' "${bench_reverse[@]}"
run_benchmark_structure_case "${bench_reverse[@]}"
run_disorder_case 'Disorder de entrada ordenada' zero "${bench_base[@]}"
run_disorder_case 'Disorder de entrada reversamente ordenada' hundred "${bench_reverse[@]}"

section "Desempenho com 100 números aleatórios ($RUNS_100 execuções)"

for ((run=1; run<=RUNS_100; run++)); do
    mapfile -t values_100 < <(gen_unique 100 1 500 | shuffle_lines)
    record_input "random_100_run_$run" "${values_100[@]}"
    run_valid_sort_case "100 números - execução $run/$RUNS_100" '' 100 "${values_100[@]}"
done

section 'Comparação das quatro estratégias com a mesma entrada de 50 números'

mapfile -t values_50 < <(gen_unique 50 1 200 | shuffle_lines)
record_input 'strategy_comparison_50' "${values_50[@]}"
declare -A strategy_counts
for strategy in --simple --medium --complex --adaptive; do
    run_valid_sort_case "50 números com $strategy" "$strategy" none "${values_50[@]}"
    strategy_counts[$strategy]=$LAST_OPERATION_COUNT
done
run_valid_sort_case '50 números sem flag (padrão)' '' none "${values_50[@]}"
strategy_counts[default]=$LAST_OPERATION_COUNT

case_header 'Comparação de eficiência: --complex versus --simple'
expected '--complex geralmente usa menos instruções que --simple.'
obtained "--simple=${strategy_counts[--simple]} operações; --complex=${strategy_counts[--complex]} operações."
if (( strategy_counts[--complex] < strategy_counts[--simple] )); then
    pass
elif (( strategy_counts[--complex] == strategy_counts[--simple] )); then
    warn 'As estratégias empataram nesta entrada aleatória.'
else
    warn '--complex usou mais operações que --simple nesta entrada. Isso não invalida a ordenação, mas merece análise.'
fi

case_header 'Comparação do padrão com --adaptive na entrada de 50 números'
expected 'mesmo comportamento/quantidade da estratégia adaptive.'
obtained "padrão=${strategy_counts[default]} operações; --adaptive=${strategy_counts[--adaptive]} operações."
if (( strategy_counts[default] == strategy_counts[--adaptive] )); then
    pass
else
    warn 'As contagens diferem; confira a seleção padrão da estratégia.'
fi

section "Desempenho com 500 números aleatórios ($RUNS_500 execuções)"

for ((run=1; run<=RUNS_500; run++)); do
    mapfile -t values_500 < <(gen_unique 500 1 1000 | shuffle_lines)
    record_input "random_500_run_$run" "${values_500[@]}"
    run_valid_sort_case "500 números - execução $run/$RUNS_500" '' 500 "${values_500[@]}"
done

section 'Resumo final'

printf '\n  %bTotal:%b   %d teste(s)\n' "$BOLD" "$RESET" "$TEST_COUNT"
printf '  %bPassou:%b  %b%d%b\n' "$BOLD" "$RESET" "$GREEN$BOLD" "$PASS_COUNT" "$RESET"
printf '  %bAvisos:%b  %b%d%b\n' "$BOLD" "$RESET" "$YELLOW$BOLD" "$WARN_COUNT" "$RESET"
printf '  %bFalhou:%b  %b%d%b\n' "$BOLD" "$RESET" "$RED$BOLD" "$FAIL_COUNT" "$RESET"
printf '  %bEntradas completas:%b %s\n\n' "$BOLD" "$RESET" "$REPORT"

if (( FAIL_COUNT == 0 )); then
    printf '%bTodos os requisitos obrigatórios testados passaram.%b\n' "$GREEN$BOLD" "$RESET"
    if (( WARN_COUNT > 0 )); then
        printf '%bHá avisos de desempenho/comportamento para revisar.%b\n' "$YELLOW" "$RESET"
    fi
    exit 0
fi

printf '%bExistem falhas que precisam ser corrigidas antes da avaliação.%b\n' "$RED$BOLD" "$RESET"
exit 1
