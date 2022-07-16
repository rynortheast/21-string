
function searchSubString(puzzle, word) {
    let result = false;
    if (word.length > 0) {
        for (let y = 0; y < puzzle.length; y += 1) {
            for (let x = 0; x < puzzle[y].length; x += 1) {
    
                puzzle[y][x] == word[0] ? 1 : 0;
    
            }
        }
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
searchSubString(examplePuzzle, "like");   // true
searchSubString(examplePuzzle, "gold");   // true
searchSubString(examplePuzzle, "queen");  // true

// Level 2
searchSubString(examplePuzzle, "cake");   // true
