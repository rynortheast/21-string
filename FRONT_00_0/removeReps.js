
function removeReps(array) {
    for (let x = 0; x < array.length; x += 1) {
        let y = array.length;
        while (x != y)
            array[x] == array[y] ? array.splice(y--, 1) : y--;
    }
    return array;
}

let result = removeReps([1, 1, 2, 4, 5, 6, 6, 8, 9, 11]); // [1,2,4,5,6,8,9,11]

// console.log(`Результат: ${result}`);
