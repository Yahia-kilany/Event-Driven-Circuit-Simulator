import matplotlib.pyplot as plt

# Function to read simulation output file
def read_simulation_file(file_path):
    """
    Reads a .sim file containing simulation data.
    
    Parameters:
        file_path (str): The path to the simulation file.
    
    Returns:
        tuple: A tuple containing a list of timestamps and a dictionary of variables.
    """
    timestamps = []   # List to store unique timestamps
    variables = {}    # Dictionary to store variable data with timestamps and values

    # Open and read the file line by line
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split(',')  # Split each line by commas
            
            # Parse timestamp, variable name, and value
            timestamp = int(parts[0])
            variable = parts[1]
            value = int(parts[2])

            # Initialize data storage for a new variable
            if variable not in variables:
                variables[variable] = {'timestamps': [], 'values': []}

            # Append timestamp and value to the variable's data
            variables[variable]['timestamps'].append(timestamp)
            variables[variable]['values'].append(value)

            # Add unique timestamps to the list
            if timestamp not in timestamps:
                timestamps.append(timestamp)

    return timestamps, variables  # Return timestamps and variables dictionary

# Function to plot waveforms
def plot_waveforms(timestamps, variables):
    """
    Plots the waveforms for each variable over time.
    
    Parameters:
        timestamps (list): List of unique timestamps.
        variables (dict): Dictionary containing variable data (timestamps and values).
    """
    num_plots = len(variables)  # Number of variables to plot
    fig, plots = plt.subplots(num_plots, 1, figsize=(10, 6 * num_plots))  # Create subplots

    # Plot each variable's data in a separate subplot
    for i, (variable, data) in enumerate(variables.items()):
        plots[i].step(data['timestamps'], data['values'], label=variable, where='post')  # Step plot for waveform
        plots[i].set_xlabel('Time')         # Label x-axis as 'Time'
        plots[i].set_ylabel('Value')        # Label y-axis as 'Value'
        plots[i].set_title(f'{variable}')   # Set title to variable name
        plots[i].grid(True)                 # Enable grid for better visualization
        plots[i].legend()                   # Display legend for the variable

    plt.tight_layout()                      # Adjust layout for clear display
    plt.subplots_adjust(hspace=1)           # Add space between subplots
    plt.show()                              # Show the plot

# Main function
def main():
    """
    Main function to run the simulation file reader and waveform plotter.
    Prompts the user for a file path or uses a default path if no input is given.
    """
    # Prompt user for file path or use default if blank
    file_path = input("Enter the path of the .sim file: ")
    if not file_path.strip():               # Use default path if input is blank
        file_path = r".\ parity_checker.sim"
    
    # Read simulation data from the file and plot waveforms
    timestamps, variables = read_simulation_file(file_path)
    plot_waveforms(timestamps, variables)

# Run main function if script is executed directly
if __name__ == "__main__":
    main()
