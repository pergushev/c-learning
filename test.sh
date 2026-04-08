#!/bin/bash

PROGRAM="7d-double_array"

# Проверка наличия файла перед компиляцией
if [ ! -f "${PROGRAM}.c" ]; then
    echo "❌ Файл ${PROGRAM}.c не найден!"
    echo "Текущая директория: $(pwd)"
    echo "Файлы в директории: $(ls)"
    exit 1
fi

gcc ${PROGRAM}.c -o ${PROGRAM}

PASSED=0
FAILED=0

# Перебираем все тесты
for i in 1 2 3; do
    ./${PROGRAM} < tests/test${i}_input.txt | tr -d '\r' > my_output.txt
    
    # Сравниваем с эталоном
    if diff -q my_output.txt tests/test${i}_expected.txt > /dev/null; then
        echo "Тест $i: PASSED ✅"
        PASSED=$((PASSED + 1))
    else
        echo "Тест $i: FAILED ❌"
        echo "Ожидалось:"
        cat tests/test${i}_expected.txt
        echo "Получено:"
        cat my_output.txt
        FAILED=$((FAILED + 1))
    fi
done

echo "-------------------"
echo "Итого: $PASSED passed, $FAILED failed"
