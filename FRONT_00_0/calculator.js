// Вам надо набор функций который будет симулировать калькулятор.
// Для этого вам надо написать 9 функций, которые могут! принимать в кач - ве аргумента другую функцию, если функция передана, то надо вернуть вызов функции с числом n, иначе вернуть число n.
// Например, функция one может принять в кач - ве аргумента функцию sum, тогда в return будет sum(1).Если же в функцию не передали ничего, то она просто вернет 1.
// Также надо написать 4 функции основных арифмитических операторов, которые принимают в кач-ве аргумента первое число, а возвращают функцию, которая принмает в кач-ве аргумента второе число и возвращает их сумму/разность/частое/произведение

function one(callback) {}
function two(callback) {}
function three(callback) {}
function four(callback) {}
function five(callback) {}
function six(callback) {}
function seven(callback) {}
function eight(callback) {}
function nine(callback) {}

function plus(a) {}

function minus(a) {}

function divide(a) {}

function mult(a) {}

one(mult(three(plus(four())))); // В итоге вернется 7
