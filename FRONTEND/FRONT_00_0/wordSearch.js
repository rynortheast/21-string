
function searchSubString(puzzle, word) {
    let result = false;
    if (word.length > 1) {
        for (let y = 0; y < puzzle.length && result == false; y += 1) {
            for (let x = 0; x < puzzle[y].length && result == false; x += 1) {
                if (puzzle[y][x] == word[0]) {
                    for (let n = -1; n <= 1 && result == false; n += 1) {
                        for (let m = -1; m <= 1 && result == false; m += 1)
                            n == 0 == m ? 0 : result = checkWord(puzzle, word, y, x, [n, m]);
                    }
                }
            }
        }
    }
    return result;
}

function checkWord(puzzle, word, y, x, indent) {
    let result = false, n = y, m = x;
    for (let z = 1; z < word.length && result == false; z += 1) {
        n += indent[0], m += indent[1];
        n < 0 ? n = null : n >= puzzle.length ? n = null : 0;
        m < 0 ? m = null : m >= puzzle[y].length ? m = null : 0;
        if ((n == null || m == null) || (puzzle[n][m] != word[z]))
            break;
        z == (word.length - 1) ? result = true : 0;
    }
    return result;
}

const examplePuzzle = [
    ["b", "l", "g", "o", "l", "d", "s"],
    ["x", "k", "q", "w", "i", "j", "p"],
    ["a", "n", "w", "k", "k", "p", "n"],
    ["h", "e", "e", "e", "k", "i", "l"],
    ["q", "e", "k", "a", "y", "q", "a"],
    ["h", "u", "h", "a", "e", "a", "u"],
    ["k", "q", "j", "c", "c", "m", "r"],
];

// Level 1
let result = searchSubString(examplePuzzle, "like");    // true
result = searchSubString(examplePuzzle, "gold");        // true
result = searchSubString(examplePuzzle, "queen");       // true

// Level 2
result = searchSubString(examplePuzzle, "cake");        // true

// console.log(`Результат: ${result}`);
