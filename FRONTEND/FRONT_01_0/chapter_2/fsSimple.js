
import fs from 'fs';

const readAndWriteCallbackHell = (callback) => {
    let data = fs.readFile("./files/fsSimple/file1.txt", (error, data) => {
        error == null ? fs.writeFile("./files/fsSimple/file2.txt", data, 
        (error) => {callback(error)}) : callback(error);
    });
};

const readAndWritePromises = () => {
    let promise = new Promise((resolve, reject) => {
        let data = fs.readFile("./files/fsSimple/file1.txt", (error, data) => {
            error == null ? fs.writeFile("./files/fsSimple/file2.txt", data, 
            (error) => {error == null ? resolve() : reject()}) : reject();
        });
    })
    return promise;
};

const readAndWriteAsyncAwait = async () => {
    let result = "3 : Файл file2.txt успешно обновлен!!";
    const saveResult = (data) => {result = data};
    let data = fs.readFile("./files/fsSimple/file1.txt", (error, data) => {
        error == null ? fs.writeFile("./files/fsSimple/file2.txt", data, 
        (error) => {error == null ? 0 : saveResult("Провал!")}) : saveResult("Провал!");
    });
    return result;
};

export {
    readAndWriteAsyncAwait,
    readAndWritePromises,
    readAndWriteCallbackHell,
};

readAndWriteCallbackHell((error) => {
    error == null ? console.log(`1 : Файл file2.txt успешно обновлен!!`) :
    console.log("1 : Произошла некоторая ошибка при . . . файла!!");
});

let saveData = readAndWritePromises();
saveData.then(() => {
    console.log("2 : Файл file2.txt успешно обновлен!!");
}, () => {
    console.log("2 : Произошла некоторая ошибка при . . . файла!!");
})

let asyncData = readAndWriteAsyncAwait();
console.log(await asyncData);
