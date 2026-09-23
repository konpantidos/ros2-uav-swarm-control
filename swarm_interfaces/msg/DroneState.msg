# Unique identifier for the drone (e.g., 1, 2, 3...)
uint8 drone_id

# Position (meters)
float64 x
float64 y
float64 z

# Velocity (meters/second)
float64 vx
float64 vy
float64 vz

# Operational Status (0: Idle, 1: Takeoff, 2: Flying, 3: Landing)
uint8 status
