# Define the input and output file names
DataFileName = "U1.txt"
ResultFileName = "U2rez.txt"

# Define a class for reading data from files
class FileReader:
    def __init__(self, FileName):
        self.FileName = FileName
        self.data = self.read_file()  # Read the file data upon initialization

    def read_file(self):
        try:
            with open(self.FileName, 'r') as file:
                return file.readlines()  # Read all lines of the file
        except FileNotFoundError:
            print(f"File '{self.FileName}' not found.")
            return []  # Return an empty list if file not found

    def task_count(self):
        return int(self.data[0])  # Get the number of tasks from the first line of data

    def line_parser(self, line):
        return list(map(int, self.data[line].split()))  # Parse a line of data into integers

    def task_max_time(self):
        return self.line_parser(1)  # Get maximum time for each task

    def task_max_score(self):
        return self.line_parser(2)  # Get maximum score for each task

    def name_and_time(self):
        data = self.data[3:]  # Skip the first three lines as they contain metadata
        return [
            (
                ' '.join(parts[:-(self.task_count())]),  # Join the student name
                list(map(int, parts[-(self.task_count()):]))  # Get the time taken for each task
            ) for parts in [line.strip().split() for line in data]  # Parse each line into parts
        ]


# Initialize FileReader to read data from the input file
file_reader = FileReader(DataFileName)

# Extract task-related information and student data
task_count = file_reader.task_count()
task_max_time = file_reader.task_max_time()
task_max_score = file_reader.task_max_score()
student_list = file_reader.name_and_time()

# Initialize variables to track best score and best scoring students
best_score = float('-inf')
best_students = []

# Iterate through each student to calculate scores and find the best students
for student in student_list:
    total_time = sum(student[1])  # Calculate total time taken by the student
    total_score = sum([
        int(task_max_score[xx] / 2) if time > task_max_time[xx] else
        task_max_score[xx] if time > 0 else 0
        for xx, time in enumerate(student[1])
    ])  # Calculate total score for the student
    total_solved = sum([1 for time in student[1] if time > 0])  # Count the number of solved tasks

    # Update best score and best students if the current student has a higher score
    if total_score > best_score:
        best_score = total_score
        best_students = [(student[0], total_solved, total_time)]
    elif total_score == best_score:
        best_students.append((student[0], total_solved, total_time))

# Sort best students by the number of tasks solved (in decreasing order)
best_students_sorted = sorted(best_students, key=lambda x: x[1], reverse=True)
#  ---------------
# | IG: @korniuss |
#  ---------------
# Write the best score answers to the output file
with open(ResultFileName, "w") as file:
    file.write("{}\n".format(best_score))  # Write the best score to the file
    for student_name, solved_tasks, task_time_taken in best_students_sorted:
        file.write("{} {} {}\n".format(student_name, solved_tasks, task_time_taken))  # Write student details
