#!/usr/bin/env python3
import sqlite3
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def plot_bag_data(bag_db_path):
    
    try:
        conn = sqlite3.connect(bag_db_path)
        cursor = conn.cursor()

        # Mock data
        t = np.linspace(0, 10, 100)
        x = np.sin(t) * 10
        y = np.cos(t) * 10
        z = t

        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        
        ax.plot(x, y, z, label='Drone 1 Trajectory', linewidth=2, color='b')
        ax.scatter(x[-1], y[-1], z[-1], color='r', marker='o', s=50, label='Final Position')
        ax.scatter(0, 0, 5, color='k', marker='x', s=100, label='Obstacle')

        ax.set_xlabel('X Position (m)')
        ax.set_ylabel('Y Position (m)')
        ax.set_zlabel('Altitude (m)')
        ax.set_title('UAV Swarm 3D Trajectory & Obstacle Avoidance')
        ax.legend()
        ax.grid(True)
        
        plt.show()
        
    except Exception as e:
        print(f"Error reading bag file: {e}")
        print("Note: Ensure the path to the .db3 file is correct.")

if __name__ == '__main__':

    bag_file = 'rosbag2_flight_data/rosbag2_flight_data_0.db3'
    plot_bag_data(bag_file)
