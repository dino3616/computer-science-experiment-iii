# Programming Seminar II

## Development flow

To launch cgi server, run the following command.

```
service apache2 start
cp /workspaces/computer-science-experiment-iii/experiments/programming-seminar-ii/src/example.cgi /usr/lib/cgi-bin/example.cgi
chmod 777 /usr/lib/cgi-bin/example.cgi
```

Then, access to `http://localhost/cgi-bin/example.cgi` from your browser.
