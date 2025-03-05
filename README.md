# Transport Damage Detection Device - FYP 2022/23

## Objective
The **Transport Damage Detection System** is an embedded system designed to enhance warehouse efficiency by automatically identifying potential damage to goods during transportation and handling. This project utilizes the **Grove Beginner Kit** to implement real-time monitoring and reporting of goods in logistics and supply chain management.

## Features
- **Real-Time Damage Detection**: Uses a three-axis accelerometer to detect excessive acceleration forces and determine potential damage.
- **Automated Notifications**: Alerts operators via a web interface with visual and auditory signals when damage is detected.
- **Data Logging & Accountability**: Maintains a log of detected damage, employee actions, and timestamps for process auditing.
- **Employee Authentication**: Requires employees to log in with their ID to ensure accountability.
- **Web Interface Integration**: Enables real-time monitoring, log access, and system control via a web dashboard.
- **Reset Mechanism**: Allows software and hardware resets to clear alerts after addressing detected issues.
- **Additional Features**: Log printing, employee notes, and shift logs for better operational tracking.

## Programming Languages
- **HTML:** Structures the webpage interface.
- **CSS:** Defines the webpage layout, colors, and fonts.
- **JavaScript:** Enhances webpage interactivity and dynamic content.
- **Arduino Code:**
  - Reads and processes data from sensors.
  - Controls actuators based on received commands.

## Technologies & Frameworks
- **jQuery:** Simplifies web interface interactions and DOM manipulation.
- **Express.js:** Handles server-side routing and logic.
- **Node.js:** Powers the backend and manages real-time interactions.
- **Socket.IO:** Enables real-time, bidirectional communication between the microcontroller and the web dashboard.

## Hardware Implementation
This system leverages the **Grove Beginner Kit**, which includes:
- **Three-Axis Accelerometer:** Measures acceleration data in X, Y, and Z directions to detect sudden motion or impact.
- **Microcontroller:** Processes acceleration data and determines if predefined damage thresholds are exceeded.
- **Alarm & Visual Indicator:** Uses a buzzer and LED to notify operators of detected damage.
- **OLED Display:** Displays acceleration values and error messages.
- **Reset Button:** Allows operators to clear error states after addressing detected damage.

## Accomplishments
- Developed a real-time monitoring system that utilizes a **3-axis accelerometer** to detect potential transport damage.
- Implemented **alerts** via an on-board LED and buzzer upon detection of excessive acceleration.
- Displayed error messages and handling instructions on the **OLED display**.
- Designed a **web-based dashboard** for real-time data visualization and control.
- Added **loss control management** features, including logging, employee authentication, and printable/downloadable reports.

## System Workflow
1. **Damage Detection:** The accelerometer captures motion data, and the microcontroller analyzes it.
2. **Alert Triggering:** If an impact exceeds the threshold, the system activates a buzzer, LED, and web alert.
3. **Operator Response:** The web interface displays error messages and prompts employees for corrective actions.
4. **Logging & Accountability:** Employee interactions are logged, ensuring responsibility and process tracking.
5. **System Reset:** Operators can reset alerts via a button or password-protected web interface action.

## Future Improvements
- **Cloud Integration:** Enable remote access and historical data analysis.
- **AI-Based Damage Prediction:** Use machine learning to enhance detection accuracy.
- **Extended Hardware Support:** Integrate additional sensors for more comprehensive monitoring.

## Author
**loldwyer** 
