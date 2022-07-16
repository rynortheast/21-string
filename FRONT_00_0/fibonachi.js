
function fibo(index) {
    return index < 0 ? 0 : index == 0 ? 1 : fibo(index - 2) + fibo(index - 1);
}

let result = fibo(21);  //  Вернет - 17711

// console.log(`Результат: ${result}`);
