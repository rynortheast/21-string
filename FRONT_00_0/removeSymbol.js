
function removeString(message, symbol) {
    message = message.split('');
    for (let x = 0; x < message.length; x += 1)
        message[x].toLowerCase() == symbol.toLowerCase() ? message.splice(x, 1) : 0;
    return message.join('');
}

let result = removeString("Hello World!", "l"); //  Вернет - Helo Word!

// console.log(`Результат: ${result}`);
