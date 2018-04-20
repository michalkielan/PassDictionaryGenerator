[![Travis CI](https://travis-ci.org/michalkielan/PassDictionary.svg?branch=master)](https://travis-ci.com/michalkielan/PassDictionary)
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

And we want to login to some service. All you have to do is remember few words for example: '**Tom acid cat hammer**' or better create a mnemonic story with those words like: "**Tom** on **acid** riding on the **cat** with the **hammer**", then find each word in your dictionary, copy the passphrases to create your strong password like the picture below. Do it each time you want to login.

![test](../master/doc/pass.png)

Make sure you have few backup's of your dictionary.

## How to generate the dictionary?

Prepare the huge file with random words:
```
acid
cat
hammer
Tom
alien
Roger
...
```

Then run:

```
./pass-dict --words=words.txt --characters=5
```

Then you will see the output file with pair of five long passphrase and word


## Building

Boost library is needed
```
$ make
```



