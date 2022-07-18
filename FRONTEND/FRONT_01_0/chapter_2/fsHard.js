
import fs from "fs";

export const progressbar = async () => {
    let files = fs.readdirSync("./files/fsHard");
    let sumFiles = files.reduce((sum, file) => {
        let stats = fs.statSync("./files/fsHard/" + file);
        return sum += (stats.size / 1024);
    }, 0)
    console.log("PROGRESS: [ " + "|".repeat(100) + ` ] 100%`);
    return Math.round(sumFiles);
}

let activeProgressBar = progressbar();
console.log(await activeProgressBar);
