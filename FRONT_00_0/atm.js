
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
        result = countCurrency > 20 ? "limit exceeded" : result;
    }
    return result;
}
  
let result_1 = atm(8350);      // {5000 : 1, 2000 : 1, 1000 : 1, 200 : 1, 100 : 1, 50 : 1 }
let result_2 = atm(2570);      // Incorrect value
let result_3 = atm(100050);    // limit exceeded

// console.log(result_1);
// console.log(result_2);
// console.log(result_3);
