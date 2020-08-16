# stencode
Command-line tool to encode and decode message in images using the Least Significant Bit technique.

## How to build it ?

In order to build the project, one must clone the repo and compile project:
```shell
$ git clone git@github.com:Sangelow/stencode.git
$ cd stencode
$ make
```
The executables are located in the `bin` directory.

## How to use it ?

This program is composed of two executables:
- `stencode`: encode a message inside a png file;
- `stdecode`: decode a message from a png file.

A description of both commands can be displayed by using the `--help` arguments.
```shell
$ ./stencode --help
$ ./stdecode --help
```

The message is encoded using the Least Significant Bit technique. Note that the message can be distributed:
- continuously: the message is encoded in successive least significant bits in the image (in pixel order);
- randomly: the least significant bits receiving the message and randomly choosen.

Note that in the random case, the seed can be generated by the program (depends on the current time) or be specified by the user.

If the distribution is random, the decoder requires the seed to decode the message.

### Continuously encode and decode a message

In order to encode the message, the `stdencode` command must be used.
```shell
$ ./stencode -i input.png -m "Here is a message encoded inside an image." -o output.png
```
The `-i` argument is the name of the input png file, the `-m` argument corresponds to the message to encode and the `-o` argument corresponds to the name of the output file. Note that the name given in this exemple are the default names in the command and could be removed (it is equivalent to: `./stencode -m "Here is a message encoded inside an image."`).

Once run, this command should display:
```shell
Stenography - Encoder
 - Length of the message: 42
 - Start the encoding
 - Reading the file: input.png
 - Detected 32 bits per pixel
 - Detected 4 channels
 - Distribute the message inside the image
 - Encoding the message in the image
 - Write the new image in the file: output.png
Encoding done successfully!
Done
```

In order to decode this image, the `stdecode` must be used. The lenght of the message must be known.

```shell
$ ./stdecode -l 42 -i output.png
```
The `-i` argument is the name of the png file containing the message and the `-l` argument corresponds length of the message. The output of the following command is (used after the endoding command) is:

```shell
Stenography - Decoder
 - Length of the message: 42
 - Start the decoding
 - Reading the file: output.png
 - Detected 32 bits per pixel
 - Detected 4 channels
 - Detect the character inside the image
 - Decoding the message in the image
The message is:
Here is a message encoded inside an image.
Done
```

### Randomly encode and decode a message

In order to the encode and distribute the message randomly in the image, the seed of the pseudo-random number generator must be specified using the `-s` argument:
```shell
$ ./stencode -s 12345 -m "Here is a message encoded inside an image."
```

The output of the command is:
```shell
Stenography - Encoder
 - Length of the message: 42
 - Start the encoding
 - Reading the file: input.png
 - Detected 32 bits per pixel
 - Detected 4 channels
 - Distribute the message inside the image
 - Initialise the pseudo random number generator with the seed: 12345
 - Encoding the message in the image
 - Write the new image in the file: output.png
Encoding done successfully!
Done
```

Note that a random seed can also be generated (based on the current time) by replacing the `-s 12345` by the `-r` argumment. The seed number will also be displayed in the output.

In order to decode the message, the seed must also be specified using the `-s` argument:
```shell
$ ./stdecode -s 12345 -l 42 -i output.png
```

The output is:
```shell
Stenography - Decoder
 - Length of the message: 42
 - Start the decoding
 - Reading the file: output.png
 - Detected 32 bits per pixel
 - Detected 4 channels
 - Detect the character inside the image
 - Initialise the pseudo random number generator
 - Decoding the message in the image
The message is:
Here is a message encoded inside an image.
Done
```




## Contributing

The following branch naming convention is used: `category/issue_description`. The caterory can be:
- feature
- bugfix
- ...

The issue corresponds to the issue number in GitHub. Finally, description is a brief description. In this description, the word are separated by hyphens. For instance, a good naming is: `feature/1_encode-file`.
