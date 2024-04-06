from collections import defaultdict, Counter

class FileReader:
    def __init__(self, FileName):
        self.FileName = FileName
        self.data = self.read_file()

    def read_file(self):
        try:
            with open(self.FileName, 'r') as file:
                return file.readlines()  # Read all lines of the file and return them
        except FileNotFoundError:
            print(f"File '{self.FileName}' not found.")
            return []  # If file not found, return an empty list

    def get_data_parsed(self):
        day_count = int(self.data[0])  # Extract the number of days from the first line of data
        # Parse each line of data after the first line and split it into a list of strings
        return [line.split() for line in self.data[1:1+day_count]]


def process_data(data_parsed):
    exercise_counts = defaultdict(lambda: [0, 0])  # Default dict to store exercise counts and total time
    time_of_day_counts = defaultdict(Counter)  # Default dict to store counts of exercises by time of day

    for day_data in data_parsed:  # Iterate over parsed data for each day
        for i in range(int(day_data[0])):  # Iterate over the exercises for each day
            # Extract exercise, time of day, and time spent from the current day's data
            exercise, time_of_day, time = day_data[i * 3 + 1: i * 3 + 4]
            # Increment total time and count for the current exercise
            exercise_counts[exercise][0] += int(time)
            exercise_counts[exercise][1] += 1
            # Increment the count of the current exercise for the current time of day
            time_of_day_counts[exercise][time_of_day] += 1

    return exercise_counts, time_of_day_counts  # Return the processed exercise counts and time of day counts


def write_results(exercise_counts, time_of_day_counts):
    with open(ResultFileName, "w") as file:  # Open a file to write results
        # Sort exercises alphabetically
        sorted_exercises = sorted(exercise_counts.items(), key=lambda x: x[0])
        for exercise, (total_time, count) in sorted_exercises:  # Iterate over sorted exercises
            # Write exercise name, count, and total time spent on the exercise
            file.write(f"{exercise} {count} {total_time}\n")
            time_of_day_order = ['Rytas', 'Diena', 'Vakaras']  # Order of time of day
            for time_of_day in time_of_day_order:  # Iterate over time of day
                time_count = time_of_day_counts[exercise][time_of_day]
                if time_count > 0:
                    # Write time of day and count for the current exercise if count is greater than 0
                    file.write(f"{time_of_day} {time_count}\n")

if __name__ == "__main__":
    DataFileName = "U2.txt"  # Input file name
    ResultFileName = "U2rez.txt"  # Output file name

    file_reader = FileReader(DataFileName)  # Create a file reader instance
    data_parsed = file_reader.get_data_parsed()  # Parse data from the input file

    exercise_counts, time_of_day_counts = process_data(data_parsed)  # Process parsed data

    write_results(exercise_counts, time_of_day_counts)  # Write processed results to output file


# -------------------
# | IG: @korniusss  |
# -------------------