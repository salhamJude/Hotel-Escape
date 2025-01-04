import matplotlib.pyplot as plt
import pandas as pd
# Data from the image extracted manually
data2 = [
    [42, 59, 38, 28, 24],
    [32, 22, 22, 25, 41],
    [38, 40, 31, 52, 40],
    [22, 52, 33, 27, 37],
    [46, 32, 20, 50, 43],
    [27, 29, 24, 15, 24],
    [31, 4, 34, 60, 37],
    [32, 46, 30, 32, 40],
    [35, 20, 34, 46, 39],
    [55, 25, 33, 54, 41],
    [22, 44, 51, 42, 36],
    [14, 24, 12, 33, 22],
    [36, 52, 19, 47, 50],
    [29, 21, 17, 9, 21],
    [33, 31, 26, 18, 7],
    [40, 34, 17, 27, 23],
    [23, 41, 21, 29, 20],
    [28, 22, 35, 21, 45],
    [32, 27, 16, 30, 16],
    [23, 29, 31, 42, 13]
]

# Convert to DataFrame
df2 = pd.DataFrame(data2, columns=["Obs1", "Obs2", "Obs3", "Obs4", "Obs5"])

# Calculate means and ranges
df2['Mean'] = df2.mean(axis=1)
df2['Range'] = df2.max(axis=1) - df2.min(axis=1)

print(df2)
# Constants for control limits for n=5 (based on standard control chart tables)
A2 = 0.577  # for the X-bar chart
D3 = 0      # for the R-chart
D4 = 2.114  # for the R-chart

# Calculate overall mean and average range
X_double_bar = df2['Mean'].mean()
R_bar = df2['Range'].mean()

# Control limits for X-bar chart
UCL_X = X_double_bar + A2 * R_bar
LCL_X = X_double_bar - A2 * R_bar

# Control limits for R-chart
UCL_R = D4 * R_bar
LCL_R = D3 * R_bar

# Plotting the X-bar and R charts
fig, ax = plt.subplots(2, 1, figsize=(12, 10))

# X-bar chart
ax[0].plot(df2['Mean'], marker='o', linestyle='-', color='blue', label='Sample Means')
ax[0].axhline(X_double_bar, color='green', linestyle='--', label='Center Line (Mean)')
ax[0].axhline(UCL_X, color='red', linestyle='--', label='UCL')
ax[0].axhline(LCL_X, color='red', linestyle='--', label='LCL')
ax[0].set_title('X-bar Chart')
ax[0].set_xlabel('Sample Number')
ax[0].set_ylabel('Mean')
ax[0].legend()
ax[0].grid(True)

# R chart
ax[1].plot(df2['Range'], marker='o', linestyle='-', color='purple', label='Sample Ranges')
ax[1].axhline(R_bar, color='green', linestyle='--', label='Center Line (Mean Range)')
ax[1].axhline(UCL_R, color='red', linestyle='--', label='UCL')
ax[1].axhline(LCL_R, color='red', linestyle='--', label='LCL')
ax[1].set_title('R Chart')
ax[1].set_xlabel('Sample Number')
ax[1].set_ylabel('Range')
ax[1].legend()
ax[1].grid(True)

plt.tight_layout()
plt.show()

(X_double_bar, R_bar, UCL_X, LCL_X, UCL_R, LCL_R)
