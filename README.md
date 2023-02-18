# lts
Alternative of `ls` command where it focuses on sorting the files in the
directory by `atime`, `ctime` and `mtime`.

## Usage 
Often time you are in the `~/Downloads` directory and you just want to
pick the most recent downloaded file. `ls -ltr` accomplishes this objective but
the output is hard to parse to be used for other command to work with.  ```sh $
lts -r ``` The above command will sort the output of current directory in
reverse.

## License 
### GNU General Public License v3.0 
Permissions of this strong copyleft license are conditioned on making available
complete source code of licensed works and modifications, which include larger
works using a licensed work, under the same license. Copyright and license
notices must be preserved.  Contributors provide an express grant of patent
rights.
