# Setup
To set up the SDK and prepare for use, follow these steps:

## 1. Execute the setup script:
```
bash install.sh
```
## 3. Folder Structure:

After extraction, your folder structure should look like this:
```
FaceDetection
HumanDecteion
nbsdk
```

### NOTE: For Windows OS, it is recommended to configure the exact destination directory for your binary files by setting WINDOWS_PATH="/mnt/c/" in the creatNBF.sh file located in each subdirectory.


# Sensor Protocol Documentation

## 1. Overview

This document describes the communication protocol used by the sensor, primarily focusing on its UART output for various detection events. The sensor outputs real-time data related to motion and specific object detections (e.g., Face, Human) via a UART interface. The data is formatted into distinct packets, allowing external systems to interpret the sensor's current state and detected object locations.

## 2. UART Protocol

The sensor transmits data over a standard UART (Universal Asynchronous Receiver/Transmitter) interface.

* **Baud Rate:** 115200

* **Data Bits:** 8

* **Parity:** None

* **Stop Bits:** 1

* **Flow Control:** None

### 2.1 Data Packet Structure

Each data packet transmitted by the sensor follows a consistent format:

`# {detect_type} $ {x0} {y0} {w} {h} \n`

* `#`: Start-of-packet delimiter.

* `{detect_type}`: A single character indicating the type of event detected.

* `$`: Separator between the detection type and coordinate data.

* `{x0}{y0}{w}{h}`: Eight-digit string representing the coordinates and dimensions of the detected area. Each value (x0, y0, w, h) is a two-digit hexadecimal number. These values are typically scaled (e.g., divided by 10 as seen in the code) from the internal sensor coordinates.

  * `x0`: X-coordinate of the top-left corner.

  * `y0`: Y-coordinate of the top-left corner.

  * `w`: Width of the detected bounding box.

  * `h`: Height of the detected bounding box.

* `\n`: Newline character, indicating the end of a packet.

**Note on Coordinates:** The coordinates `(x0, y0, w, h)` represent a bounding box around the detected object or motion area. The origin `(0,0)` is typically the top-left corner of the sensor's field of view.

### 2.2 Motion Detection (`detect_type = '0'`)

When no specific object (like Face or Human) is detected, but general motion is observed, the sensor outputs a packet with `detect_type` set to `'0'`. The coordinates `(x0)(y0)(w)(h)` represent the bounding box of the detected motion.

* **Protocol Example:** `#0$(x0)(y0)(w)(h)`

* **Context:** Used when the sensor is in a "motion-only" state or when no specific object model is triggered.

## 3. Face Detection

* **`detect_type = 'F'`**

* Indicates that a human face has been detected.

* **Distance Range:** 0.5m - 1.5m (optimal detection distance for faces).

* The coordinates `(x0)(y0)(w)(h)` represent the bounding box of the detected face.

* **Protocol Example:** `#F$(x0)(y0)(w)(h)`

## 4. Human Detection

* **`detect_type = 'H'`**

* Indicates that a human body has been detected.

* **Distance Range:** 0.5m - 2.5m (optimal detection distance for human bodies).

* The coordinates `(x0)(y0)(w)(h)` represent the bounding box of the detected human.

* **Protocol Example:** `#H$(x0)(y0)(w)(h)`



