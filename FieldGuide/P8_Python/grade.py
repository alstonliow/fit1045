class grade_analyser:
    def __init__(self):
        self.grades = []

    #add one grade
    def add_grade(self, g):
        self.grades.append(g)

    #add many grades
    def add_grades(self):
        count = int(input("How many grades? "))
        for i in range(count):
            g = int(input(f"Grade {i + 1} : "))
            self.grades.append(g)

    #add grades by list
    def add_grades_list(self, g):
        self.grades += g

    #average
    def average(self):
        total = 0
        for g in self.grades:
            total += g
        return total / len(self.grades)

    #pass_rate
    def pass_rate(self):
        num_pass = 0
        for g in self.grades:
            if g >= 50:
                num_pass += 1
        return num_pass / len(self.grades) * 100

    #num_hd
    def num_hd(self):
        num_hd = 0
        for g in self.grades:
            if g >= 80:
                num_hd += 1
        return num_hd

if __name__ == "__main__":
    analyser = grade_analyser()
    analyser.add_grades()

    print(f"Average: {analyser.average()}")
    print(f"Pass rate: {analyser.pass_rate()}%")
    print(f"High distinctions: {analyser.num_hd()}")