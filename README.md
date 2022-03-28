# Parser

The application receives two parameters: the first is path to file or folder, the second one is a string to be searched for (up to 128 characters). It prints occurances of provided string in text files in format "file_name(offset): prefix...suffix", where offset is a position within the file where the string started, prefix are three characters before matched string and suffix are three characters after matched string.
