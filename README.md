Zip-Case-X File Protector SV
============================

This is the **"Stable Version"** of my File Protection programs
circa 2001.

## Compatibility

There are some compatibility rules you would want to follow, if
the files encrypted in one OS need to be compatible with the
others too.

* Ensure that the file names are in the **DOS 8.3 format**
(such as `.HTM`, `.MPG` ) for best compatibility.

* The files must ideally be in the current working
directory. Avoid usage of `.` and `..` or directory
separators such as `/` or `\` in files, we don't try
to interpret them.

* Ideally, the files are meant to be less than 2GB, to
allow working on the older compilers without many issues. No
guarantees are made on files larger or equal to that size. Use
compression and file size splitting to ensure you do not
encounter these bugs when running this program.

## How to Use

Go to the Appropriate Binary Executables Directory. Then Use:

```shell
  encom File <Encrypted File, Default is FPCODED.ZCX>
```

to encrypt your file, and

```shell
  decom <Encrypted File, Default is FPCODED.ZCX>
```

to restore your original file.

## Restrictions

This should not be used for any illegal purposes whatsoever.
Use your judgment.

Please see accompanying `LICENSE` for how this code is meant
to be used.

## Version Compatibility

When you use the most current version, files in the previous
versions are not guaranteed to work. So please retain older versions of
executables for decrypting.

## Thank You and Feedback

Reach out to me for any feedback.

Now Enjoy!

* Author: Karthik Kumar Viswanathan
* Web   : https://karthikkumar.org
* Email : karthikkumar@gmail.com
