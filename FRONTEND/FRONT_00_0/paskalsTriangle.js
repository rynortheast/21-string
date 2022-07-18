
function paskalsTriangle(x, y) {
    return (x == y || x == 0) ? 1 : paskalsTriangle(x - 1, y - 1) + paskalsTriangle(x, y - 1);
}

let result = paskalsTriangle(3, 6);     //  Вернет - 3

// console.log(`Результат: ${result}`);

// for (let y = 0; y <= 8; y += 1) {
//     let line = [];
//     for (let x = 0; x != (y + 1); x += 1)
//         line.push(paskalsTriangle(x, y));
//     console.log(line.join(', '));
// }
