
import { Empleyee } from "./classes.js";

export class Company {
    constructor(companyName) {
        this.staff = {'manager': [], 'developers': [[], []]};
        this.companyName = companyName;
        this.completedProjects = [];
        this.currentProject = [];
    }
    addNewCompanyMember(empleyee) {
        (empleyee instanceof FrontendDeveloper) ? this.staff['developers'][1].push(empleyee) : 0;
        (empleyee instanceof BackendDeveloper) ? this.staff['developers'][0].push(empleyee) : 0;
        (empleyee instanceof Manager) ? this.staff['manager'].push(empleyee) : 0;
    }
    getMembersQuantity() {
        return this.staff['manager'].length + 
        this.staff['developers'][0].length + 
        this.staff['developers'][1].length;
    }
    addProject(project) {this.currentProject.push(project)};
}

export class Project {
    constructor(projectName, minQualification) {
        this.team = {'manager': [], 'developers': {'frontend': [], 'backend': []}};
        this.minQualification = minQualification;
        this.projectName = projectName;
    }
    completeProject() {console.log("Проект закрыт!!");}
    addNewProjectMember(empleyee) {
        (empleyee instanceof FrontendDeveloper) ? this.team['developers']['frontend'].push(empleyee) : 0;
        (empleyee instanceof BackendDeveloper) ? this.team['developers']['backend'].push(empleyee) : 0;
        (empleyee instanceof Manager) ? this.team['manager'].push(empleyee) : 0;
    }
}

export class Manager extends Empleyee {
    constructor(name, grade, company, projectQuantity) {
        super(name, grade, company);
        this.projectQuantity = projectQuantity;
    }
    checkMember(minQuantity, empleyee) {return (empleyee.grade[1] >= minQuantity[1]);}
}

export class FrontendDeveloper extends Empleyee {
    constructor(name, grade, company, developerSide, projectQuantity) {
        super(name, grade, company);
        this.projectQuantity = projectQuantity;
        this.developerSide = developerSide;
        this.stack = [];
    }
    expandStack(someTech) {this.stack.push(someTech);}
}

export class BackendDeveloper extends Empleyee {
    constructor(name, grade, company, developerSide, projectQuantity) {
        super(name, grade, company);
        this.projectQuantity = projectQuantity;
        this.developerSide = developerSide;
        this.stack = [];
    }
    expandStack(someTech) {this.stack.push(someTech);}
}

let MGYpi = new Company("MGYpi");
let s21_string = new Project("s21_string", "L2");
let narisa = new Manager("Sasha", "L2", "MGYpi", 0);
let eunostus = new BackendDeveloper("Artem", "L2", "MGYpi", "backend", 0);
let chamomil = new FrontendDeveloper("RV304", "L2", "MGYpi", "frontend", 0);

MGYpi.addNewCompanyMember(narisa);
MGYpi.addNewCompanyMember(chamomil);
MGYpi.addNewCompanyMember(eunostus);

s21_string.addNewProjectMember(narisa);
s21_string.addNewProjectMember(chamomil);
s21_string.addNewProjectMember(eunostus);
MGYpi.addProject(s21_string);

console.log(MGYpi);
