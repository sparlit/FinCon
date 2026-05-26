# Testing FinCon Terminal

This project uses the Qt Test framework for automated verification of core systems.

## Prerequisites

Ensure you have the development environment set up:
- Qt 6 (Widgets, Charts, Network, Sql, Test)
- CMake 3.27+
- Ninja Build
- Python 3.11

## Build and Run Tests

1.  **Configure and Build**:
    ```bash
    mkdir build && cd build
    cmake .. -GNinja
    ninja FinConTests
    ```

2.  **Execute Tests**:
    ```bash
    ./FinConTests
    ```

## Manual Verification (End-to-End)

To verify the UI and DataHub integration:

1.  **Run the Terminal**:
    ```bash
    ./FinConTerminal
    ```
    *(Note: If running on Linux without a display, use `export QT_QPA_PLATFORM=offscreen` for headless verification)*

2.  **Login**: Use any non-empty email and password to authenticate through the mock backend.
3.  **Navigate**: Use the sidebar to switch between Dashboard, Markets, and QuantLib Suite.
4.  **Command Bar**: Press `Ctrl+K` to toggle the command bar.
5.  **Analytics**: In the QuantLib Suite screen, change the tool selection to see mock parameter calculations updating.
6.  **DataHub**: Check `terminal.log` to verify the DataHub scheduler is ticking and expiring old topics.

## Troubleshooting

- If compilation fails due to `QT_NO_CAST_FROM_ASCII`, ensure the `sed` command in the build script has been applied to the QXlsx dependency.
- For secure storage errors on Linux, ensure `libsecret-1-dev` is installed.
