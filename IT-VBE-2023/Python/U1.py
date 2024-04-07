class FileReader:
    def __init__(self, FileName):
        self.FileName = FileName
        self.data = self.read_file()  # Read the file upon initialization

    def read_file(self):
        try:
            with open(self.FileName, 'r') as file:
                return file.readlines()  # Read all lines from the file
        except FileNotFoundError:
            print(f"File '{self.FileName}' not found.")
            return []  # Return an empty list if file not found

    def data_sorting(self):
        time_array = []

        # Parse data, convert to integers, and filter out entries with 0 values
        for time in self.data[1:]:
            time = time.split()  # Split the line into individual values
            time = [int(x) for x in time]  # Convert values to integers
            if 0 not in time:  # Check if any value is 0
                time_array.append(time)  # Append non-zero entries to the array
        return time_array


def calculate_sum(data):
    result = []
    
    # Count occurrences of each group and sum the distance for each group
    group_counts = find_groups(data)
    for i, (group, count) in enumerate(group_counts.items()):
        temp = 0
        for steps in data:
            if steps[0] == group:
                # Calculate distance for each group, rounding to 2 decimal places
                temp += round(steps[1] / 100000 * sum(steps[2:]), 2)
        result.append(temp)  # Append the calculated sum for each group to the result list

    return group_counts, result


def find_groups(data):
    group_counts = {}
    # Count occurrences of each group
    for groups in data:
        group = int(groups[0])  # Extract group number
        if group in group_counts:
            group_counts[group] += 1
        else:
            group_counts[group] = 1
    return group_counts


def write_results(data_calculated, distance, ResultFileName):
    # Write calculated results to the output file
    with open(ResultFileName, "w") as file: 
        for i, (group, count) in enumerate(data_calculated.items()):
            file.write(f"{group} {count} {distance[i]}\n")


if __name__ == "__main__":
    DataFileName = "U1.txt"  # Input file name
    ResultFileName = "U1rez.txt"  # Output file name

    # Create a file reader instance and parse data from the input file
    file_reader = FileReader(DataFileName)
    data_sorted = file_reader.data_sorting()

    # Calculate sum for each group and write results to output file
    data_calculated, distance = calculate_sum(data_sorted)
    write_results(data_calculated, distance, ResultFileName)

# -------------------
# |  IG: Korniusss  |
# -------------------