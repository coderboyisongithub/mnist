# synapse_mnist
- *what is this?*
- *Cult of endianness*
- *Challenge faced reading mnist file*
- *Algorithm that address challenge*
- *functions from header*


## What is this?

This is a c++ single header to read binary format of mnist dataset.

## Cult of endianess in computing

While mnist is an common ground to demonstrate small netowrk.But with the same time its classic.When mnist dataset were prepared,Its creators were working in AT&T labs.During that time the lab was equipped with IBM power pc,motorola and other ancestor that belonged to my laptop I am writing this doc with.

Mnist creators used any one of these to build dataset into idx binary.All processors used over those systems were *Big endian*.Currently intel and amd are little endian,arm on other hand is both on choice.
*creators of mnist must have communicated "we are using big endian"*,Life could have been easier.

## Challange in accessing data from idx(binary)

As a result of this.Big endian data is represented as little endian.Most significant "Byte" is switched with Least significant "Byte".One of the core algorithm here is to reverse the big endian to little endian.


## Proposed algorithm for big2little endian

Before designing the algorithm, a picture need to be drawn about memory layout.
very first informating in mnist file is magic number=2051(0x803)

Big endian.(how it shall be laid in memory)

|byte0|byte1|byte2|byte3|
|---|---|---|---|
| 30| 80| 00|00 |

 big endian.(how it is laying out)

|byte3|byte2|byte1|byte0|
|---|---|---|---|
| 00| 00| 80|03 |


```cpp
int little = (big & 0xFF000000) >> 24;
little = (big & 0x00FF0000) >> 8 | little;
little = (big & 0x0000FF00) << 8 | little;
little = (big & 0x000000FF) << 24 | little;
return little;
```

## functions from header
- `load(std::string imagepath, std::string lablepath) ;`

*function:* read mnist file and prepare image(unsigned char x 784 each) and lable(unsigned char) vector

*return:* void

- `operator []`

*function:* access operator for prepared image and lables.

*return:* `std::pair<int,int>` where first=number of images,second number of lables


