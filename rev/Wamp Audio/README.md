# Wamp Audio

Wamp Audio is a RIFF Wave file re-encoder that runs run length encoding on each byte of segment sizes 4000 bytes, pads the results with zeros, and writes it to a new file of segment size 8000 bytes.

The only difference between Wamp and Wave is the headers magic number is changed from RIFF --> WAMP and WAVE --> ADIO.

# Solve

To solve, extract each frame of size 8000, decode the run length encoding, and write it to a new wave file.