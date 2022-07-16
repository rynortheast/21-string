"use strict";

let sum = -3;

function counter() {
    return sum += 3;
}

counter(); // Функция вернет 0
counter(); // Функция вернет 3
counter(); // Функция вернет 6
counter(); // Функция вернет 9

console.log(`Результат: ${sum}`);
