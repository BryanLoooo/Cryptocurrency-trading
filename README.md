### 📘 **README.md**

```markdown
# 🎧 DJ Music Player – Object-Oriented Audio Mixing Application

A professional **DJ Music Player** developed using **Object-Oriented Programming (OOP)** concepts.  
This application enables users to mix, manipulate, and control multiple tracks simultaneously through a **custom-built interface** inspired by modern DJ consoles.

---

## 🧠 Project Overview

This project was designed as part of an **Object-Oriented Programming coursework**, focusing on encapsulation, modularity, and interactivity.  
The system allows users to **load, play, pause, and mix multiple tracks**, providing hands-on experience with real-time audio manipulation and GUI-based event handling.

---

## 🕹️ Features

| Feature | Description |
|----------|-------------|
| 🎚️ **Multi-Deck Audio Player** | Supports up to four music players simultaneously for real-time mixing. |
| ▶️ **Play & Stop Controls** | Independent play/stop buttons for each deck. |
| ⏩ **Forward & Back Buttons** | Adjust playback by a few seconds to fine-tune song position. |
| 🕒 **Live Time Display** | Displays current playback position for precision timing. |
| 🔊 **Custom Sliders** | Control speed and volume with visually styled sliders. |
| 🔁 **Waveform Visualization** | Real-time waveform updates to show current playback position. |
| ❌ **Remove Track Function** | Allows clearing a track to load new music without conflicts. |
| 🧭 **User-Friendly Interface** | Designed with clear labeling and intuitive controls for non-technical users. |

---

## 🎨 UI & Interaction Design

Inspired by a professional DJ deck interface, the layout focuses on **visual clarity and ease of control**:
- Buttons are color-coded (blue feedback when pressed).  
- Each player includes labeled sliders and position indicators.  
- Real-time waveform and position updates enhance the interactive experience.

The interface fulfills the requirement of creating a **custom UI** that simplifies technical audio control for beginners while maintaining precision for experienced users.

---

## 🧮 Implementation Highlights

| Component | Implementation Details |
|------------|------------------------|
| **Forward Button (Line 160–171)** | Increases track time by a few seconds, updates waveform position. |
| **Back Button (Line 173–184)** | Rewinds playback time, adjusts the slider position visually. |
| **Time Label** | Continuously updates to reflect the song’s current playhead position. |
| **Slider Styling** | Custom-designed to visually resemble physical DJ controls. |
| **Remove Button (Line 147–158)** | Clears current track and waveform for a new song load. |
| **Player Reset** | Resets transport and reader sources to refresh player state. |

All components were implemented using **modular OOP methods**, emphasizing readability and maintainability.

---

## ⚙️ Technical Concepts Applied

- **Encapsulation:** Modularized functions for loading, clearing, and updating tracks.  
- **Polymorphism:** Used for reusing button listener behaviors across different player decks.  
- **Event Handling:** Buttons, sliders, and waveform updates trigger independent functions.  
- **State Management:** Dynamic updates to player status, waveform, and playback position.  

---

## 📂 Project Structure

```

DJ_Music_Player/
├── Source/
│   ├── MainComponent.cpp
│   ├── DeckGUI.cpp
│   ├── DJAudioPlayer.cpp
│   └── WaveformDisplay.cpp
├── Assets/
│   ├── UI_Elements/
│   └── Audio/
└── README.md

```

Each module handles distinct functionalities — from UI rendering to playback logic — ensuring clean architecture and scalability.

---

## 🧰 Tools & Frameworks

| Tool | Purpose |
|------|----------|
| **JUCE Framework** | Audio processing, GUI components, and real-time playback. |
| **C++ (OOP)** | Core programming language for structure and logic. |
| **Object-Oriented Design** | For modular and maintainable codebase. |

---

## 🧭 User Interaction Flow

1. **Load Songs** using the file picker for each player.  
2. **Play or Stop Tracks** independently.  
3. **Adjust Speed & Volume** using custom sliders.  
4. **Fine-Tune Position** using back/forward buttons.  
5. **Monitor Waveform** in real time with playback updates.  
6. **Clear Tracks** with the remove button to load new audio seamlessly.

---

## 💡 Design Rationale

This DJ Music Player emphasizes:
- **Efficiency:** Quick track manipulation without complex menus.  
- **Accessibility:** Simplified interface for all users.  
- **Visual Feedback:** Real-time waveform and color changes enhance user awareness.  
- **Creative Control:** Enables intuitive song mixing and timing control.

The additional features like **forward/back time shifting**, **live labels**, and **custom sliders** were added to make the app **more engaging, ergonomic, and performance-ready**.

---

## 🚀 Future Enhancements

| Planned Feature | Description |
|------------------|-------------|
| 🎵 Looping Functionality | Enable looped playback of selected segments. |
| 🎚️ Equalizer Panel | Add adjustable frequency sliders for sound balancing. |
| 💾 Save Mixes | Export user sessions into audio files. |
| 🔁 Sync Engine | Auto-align beats across multiple decks. |

---