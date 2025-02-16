# Notepad-with-auto-suggestion-using-Huffman-Coding-C++-


This project implements a text editor that supports real-time word suggestions and efficient text compression using Huffman encoding. The editor is designed to assist users by predicting words and saving text in a compressed format.

## Features
- **Huffman Encoding**: Compresses text by encoding characters based on their frequency.
- **Trie-based Word Suggestions**: Predicts and suggests words as the user types.
- **File Persistence**: Saves and loads text with the corresponding Huffman tree.
- **Interactive Editing**: Supports word selection, navigation, and text saving.

## How It Works
1. **Calculate Frequency**: The frequency of each character is computed.
2. **Build Huffman Tree**: Characters are encoded using a Huffman tree.
3. **Trie Tree for Suggestions**: A dictionary is loaded into a trie to provide suggestions.
4. **Text Input**: Users can type text, select suggestions, and save their work.

## Usage
- **Alphabetic Characters**: Type letters to get word suggestions.
- **Space (` `)**: Finalizes a word and adds a space.
- **Period (`.`)**: Finalizes a sentence, capitalizing the next word.
- **Slash (`/`)**: Navigate through word suggestions.
- **Semicolon (`;`)**: Select a suggested word.
- **Equal Sign (`=`)**: Save the current text.
- **Enter (`Enter`)**: Exit the editor.

## File Structure
- **dictionary.txt**: Contains the words for the trie tree.
- **userText.txt**: Stores the compressed user text.
- **HuffTree.txt**: Stores the structure of the Huffman tree.

## Code Overview
- **calculate_freq**: Counts the frequency of characters.
- **Huffman Tree**: Encodes text efficiently.
- **Trie Tree**: Predicts words based on prefixes.
- **Main Loop**: Handles user input and manages suggestions.

## Compilation Instructions
Use a C++ compiler (e.g., g++) to compile the code:
```bash
g++ -o text_editor text_editor.cpp
./text_editor
```

## Example
```plaintext
Welcome to Text Editor
1. Enter new text
2. Load a saved text

Input text while getting live word suggestions. Press `=` to save and `Enter` to exit.
```

This editor provides a combination of predictive text functionality and text compression, making it suitable for basic text entry tasks.

