# Passwords Dictionary Generator

This application is for generating the dictionary of pair passphrase and word. Each N characters passphrase is connected to one random word from the input file. 

## How to use the passphrase dictionary?

Let's say we have a dictionary like this:

```
...
4^&d2  acid
r#c01  cat
Ma2#s  hammer
m04@s  Tom
04fg(  alien
$$fw3  Roger
...
```

And we want to login to some service. All you have to do is remember few words for example: 'Tom acid cat hammer' or better create a mnemonic story with those words like: "Tom on acid riding on the cat with the hammer", then find each word in your dictionary, copy the passphrases to create your strong password like the picture below. Do it each time you want to login.

![test](../master/doc/pass.png)

Make sure you have few backup's of your dictionary.

## How to generate the dictionary

Prepare the huge file with random words, then run:

```
./pass-dict --words=words.txt --characters=5
```

Then you will see the output file with pair of five log passphrase and word


## How to generate the dicionary with numbers

```
./pass-dict --words=words.txt --characters=5 --numbers-only
```

Then you will see the output file with pair of five digits number and word

```
00000 word1
00001 word2
...
99999 word3
```


