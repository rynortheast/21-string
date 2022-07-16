
function atm(sum) {
    const banknots = [5000, 2000, 1000, 500, 200, 100, 50];
    let result = "Incorrect value";
    if (sum % 50 == 0) {
        let countCurrency = 0;
        result = banknots.reduce((obj, a) => {
            if ((sum / a) >= 1) {
                obj[a] = Math.floor(sum / a);
                countCurrency += obj[a];
                sum -= obj[a] * a;
            }
            return obj;
        }, {});
        countCurrency > 20 ? result = "limit exceeded" : 0;
    }
    return result;
}
  
let result = atm(8350);     // {5000 : 1, 2000 : 1, 1000 : 1, 200 : 1, 100 : 1, 50 : 1 }
result = atm(2570);         // Incorrect value
result = atm(100050);       // limit exceeded

// console.log("Результат:", result);
