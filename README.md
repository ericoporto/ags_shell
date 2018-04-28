# agsshell

I wanted to open webpages from my AGS game.

Used the code started by [monkey0506](https://bitbucket.org/monkey0506/ags_shell).

In ags script, use like below:

      if( System.OperatingSystem == eOSWindows ){
        ShellExecute("open", "rundll32.exe", "url.dll,FileProtocolHandler http://www.google.com");
      } else if( System.OperatingSystem == eOSLinux ){
        ShellExecute("", "", "xdg-open http://www.google.com");
      }

[**Go here to grab the latest release**](https://github.com/ericoporto/agsshell/releases)!
