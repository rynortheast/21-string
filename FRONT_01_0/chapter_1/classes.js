
export class Empleyee {
    constructor(name, grade, hardSkills, company) {
        this.name = name;
        this.grade = grade;
        this.company = company;
        this.hardSkills = hardSkills;
    }
    addSkill(newSkillName) {this.hardSkills.push(newSkillName);}
    changeCompany(newCompanyName) {this.company = newCompanyName;}
    upGrade() {this.grade[1] != '4' ? this.grade = "L" + (Number(this.grade[1]) + 1) : 0;}
    viewCard() {
        console.log(`\nИнформация о работнике:\nИмя: ${this.name}\nУровень: ` +
        `${this.grade}\nКомпания: ${this.company}\nНавыки: ${this.hardSkills}\n`);
    }
}

let chamomil = new Empleyee("RV304", "L2", ["fuss"], "MGYpi");
chamomil.viewCard();

chamomil.changeCompany("YANDEX.EDA");
chamomil.addSkill("irritability");
chamomil.upGrade();
chamomil.viewCard();
