import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

# NOTE: This code was mostly generated using an LLM (Deepseek)

def moving_average_filter(df, N):
    df_filtered = df.copy()

    # Apply moving average to all columns except 'time'
    for col in df.columns:
        if col != 'time':
            # Use min_periods=1 to avoid NaN values at the start
            df_filtered[col] = df[col].rolling(window=N, min_periods=1).mean()
    return df_filtered

def plot_accel(df, filter_N=0, save_fig=False):
    # Initialize time to 0
    df['time'] = df['time'] - df['time'][0]

    # Plotting Accelerometer Data
    plt.figure(figsize=(12, 6))
    plt.plot(df['time'], df['accelX'], label='accelX', color='r')
    plt.plot(df['time'], df['accelY'], label='accelY', color='g')
    plt.plot(df['time'], df['accelZ'], label='accelZ', color='b')
    if filter_N != 0:
        plt.title(f'Accelerometer Data with moving average filter N={filter_N}')
    else:
        plt.title('Accelerometer Data')
    plt.xlabel('Time (s)')
    plt.ylabel('Acceleration (g)')
    plt.legend()
    plt.grid(True)
    if save_fig:
        if not os.path.exists('accel_plots'):
            os.makedirs('accel_plots')
        if filter_N != 0:
            plt.savefig(f'accel_plots\\accel_data_filter_{filter_N}')
        else:
            plt.savefig(f'accel_plots\\accel_data_raw')
    else:
        plt.show()

def plot_gyro(df, filter_N=0, save_fig=False):
    # Initialize time to 0
    df['time'] = df['time'] - df['time'][0]

    # Plotting Gyroscope Data
    plt.figure(figsize=(12, 6))
    plt.plot(df['time'], df['gyroX'], label='gyroX', color='r')
    plt.plot(df['time'], df['gyroY'], label='gyroY', color='g')
    plt.plot(df['time'], df['gyroZ'], label='gyroZ', color='b')
    if filter_N != 0:
        plt.title(f'Gyroscope Data with moving average filter N={filter_N}')
    else:
        plt.title('Gyroscope Data')
    plt.xlabel('Time (s)')
    plt.ylabel('Angular Velocity (rad/s)')
    plt.legend()
    plt.grid(True)
    if save_fig:
        if not os.path.exists('gyro_plots'):
            os.makedirs('gyro_plots')
        if filter_N != 0:
            plt.savefig(f'gyro_plots\\gyro_data_filter_{filter_N}')
        else:
            plt.savefig(f'gyro_plots\\gyro_data_raw')
    else:
        plt.show()


def plot_displacement(df, filter_N=0, save_fig=False):
    time = df['time'] - df['time'][0]
    fs = 100  # Sampling frequency (Hz) — adjust to match your IMU settings
    dt = 1 / fs  # Time step

    # Process all three axes
    displacements = {}
    for axis in ['X', 'Y', 'Z']:
        # Convert g to m/s² and remove gravity (for Z-axis)
        accel = df[f'accel{axis}'].values * 9.81  # Convert to m/s²
        if axis == 'Z':
            accel -= 9.81  # Remove gravity (adjust if your IMU orientation differs)

        # Double integration: Acceleration → Velocity → Displacement
        velocity = np.cumsum(accel * dt)
        velocity_detrended = velocity - np.mean(velocity)  # Remove DC drift
        displacement = np.cumsum(velocity_detrended * dt)

        displacements[axis] = displacement

    # Plot Displacement for All Axes
    plt.figure(figsize=(12, 8))

    # X-axis
    plt.subplot(3, 1, 1)
    plt.plot(time, displacements['X'], color='r', linewidth=1.5)
    if filter_N != 0:
        plt.title(f'Displacement (X) with moving average filter N={filter_N}')
    else:
        plt.title(f'Displacement (X)')
    plt.ylabel('Meters', fontsize=10)
    plt.xlabel('Time (s)', fontsize=10)
    plt.grid(True, linestyle='--', alpha=0.7)

    # Y-axis
    plt.subplot(3, 1, 2)
    plt.plot(time, displacements['Y'], color='g', linewidth=1.5)
    if filter_N != 0:
        plt.title(f'Displacement (Y) with moving average filter N={filter_N}')
    else:
        plt.title(f'Displacement (Y)')
    plt.ylabel('Meters', fontsize=10)
    plt.xlabel('Time (s)', fontsize=10)
    plt.grid(True, linestyle='--', alpha=0.7)

    # Z-axis
    plt.subplot(3, 1, 3)
    plt.plot(time, displacements['Z'], color='b', linewidth=1.5)
    if filter_N != 0:
        plt.title(f'Displacement (Z) with moving average filter N={filter_N}')
    else:
        plt.title(f'Displacement (Z)')
    plt.xlabel('Time (s)', fontsize=10)
    plt.ylabel('Meters', fontsize=10)
    plt.grid(True, linestyle='--', alpha=0.7)

    plt.tight_layout()
    if save_fig:
        if not os.path.exists('displacement_plots'):
            os.makedirs('displacement_plots')
        if filter_N != 0:
            plt.savefig(f'displacement_plots\\displacement_data_filter_{filter_N}')
        else:
            plt.savefig(f'displacement_plots\\displacement_data_raw')
    else:
        plt.show()

if __name__ == "__main__":
    df = pd.read_csv("4_imu_calibrated.csv.txt")
    plot_accel(df, save_fig=True)
    plot_gyro(df, save_fig=True)
    plot_displacement(df, save_fig=True)

    # apply moving average with window size = 30
    N_vals = [10, 20, 30, 50, 100, 200, 500]

    for N in N_vals:
        df = moving_average_filter(df, N)
        plot_accel(df, N, save_fig=True)
        plot_gyro(df, N, save_fig=True)
        plot_displacement(df, N, save_fig=True)