<div align="center">

# Changelog of ft_irc

## Versions history

<br>

|            Version             |       Tag        | Importance | Runnable |
| ------------------------------ | ---------------- | ---------- | -------- |
| [1.7.1](#latest-171---major)   |  Latest, !join   |  `major`   |    ✅    |
| [1.7.0](#170---minor)          |       Norm       |  `minor`   |    ✅    |
| [1.6.6](#166---minor)          |                  |  `minor`   |    ✅    |
| [1.6.4](#164---major)          |      !help       |  `major`   |    ✅    |
| [1.6.0](#160---major)          |     Internet     |  `major`   |    ✅    |
| [1.5.5](#155---minor)          |                  |  `minor`   |    ✅    |
| [1.5.3](#153---major)          |      LISTv2      |  `major`   |    ✅    |
| [1.5.1](#151---minor)          |                  |  `minor`   |    ✅    |
| [1.5.0](#150---major)          |     IRCBotv2     |  `major`   |    ✅    |
| [1.4.2](#142---minor)          |                  |  `minor`   |    ✅    |
| [1.4.1](#141---major)          |   LIST, USERS    |  `major`   |    ✅    |
| [1.4.0](#140---major)          |      IRCBot      |  `MAJOR`   |    ✅    |
| [1.3.3](#133---minor)          |                  |  `minor`   |    ✅    |
| [1.3.2](#132---major)          |     Hostname     |  `major`   |    ✅    |
| [1.3.0](#130---major)          |       PASS       |  `major`   |    ✅    |
| [1.2.17](#1217---minor)        |                  |  `minor`   |    ✅    |
| [1.2.15](#1215---minor)        |                  |  `minor`   |    ✅    |
| [1.2.14](#1214---major)        |   identifiers    |  `major`   |    ✅    |
| [1.2.12](#1212---major)        |      NAMES       |  `major`   |    ✅    |
| [1.2.11](#1211---major)        |       KICK       |  `major`   |    ✅    |
| [1.2.10](#1210---minor)        |       argv       |  `minor`   |    ✅    |
| [1.2.9](#129---major)          |      INVITE      |  `major`   |    ✅    |
| [1.2.8](#128---major)          |      TOPIC       |  `major`   |    ✅    |
| [1.2.6](#126---minor)          |                  |  `minor`   |    ✅    |
| [1.2.5](#125---major)          |       MODE       |  `major`   |    ✅    |
| [1.2.0](#120---major)          |     Channels     |  `major`   |    ✅    |
| [1.1.1](#111---minor)          |                  |  `minor`   |    ✅    |
| [1.1.0](#110---major)          |     Commands     |  `major`   |    ❌    |
| [1.0.3](#103---minor)          |                  |  `minor`   |    ✅    |
| [1.0.2](#102---major)          |                  |  `major`   |    ✅    |
| [1.0.0](#first-100---major)    |     Initial      |  `major`   |    ✅    |

<br>

## Server's Commands

<br>

| State  |                                Command                                 |                      Usage                       | Description |
| ------ | ---------------------------------------------------------------------- | ------------------------------------------------ | ----------- |
|   ✅   | [USER](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.3)    | `USER <username> * * <realname>`                 | **Needed to register.** <br> Setup username and real name. |
|   ✅   | [NICK](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.2)    | `NICK <nickname>`                                | **Needed to register.** <br> Setup or change nickname. <br> The nickname MUST be UNIQUE. |
|   ✅   | [PASS](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.1)    | `PASS <password>`                                | **Needed to register.** <br> Set the password used to join <br> the server. It MUST be executed <br> BEFORE the combinaison <br> `USER` / `NICK`. |
|   ✅   | [QUIT](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.6)    | `QUIT [<message>]`                               | Disconnect properly, informing the <br> other clients, leaving channels. |
| &nbsp; |                                                                        |                                                  |             |
|   ✅   | [JOIN](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.1)    | `JOIN <channel>[,...] <keys>[,...]`              | Join channels, using keys if <br> necessary. The channels' names <br> MUST start with a hash (`#`) |
|   ✅   | [PART](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.2)    | `PART <channel>[,...] [<message>]`               | Quit properly channels, informing <br> the other clients, closing <br> channels if empty. |
|   ✅   | [PRIVMSG](https://datatracker.ietf.org/doc/html/rfc1459#section-4.4.1) | `PRIVMSG <receivers>[,...] <message>`            | Send a message. Receiver is either <br> **a user** or **a channel (#...)**. No <br> message should be sent to the <br> sender *(except when it is part <br> of the receivers)*. |
| &nbsp; |                                                                        |                                                  |             |
|   ✅   | [MODE](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.3)    | `MODE <channel> [[+\|-]{i\|k\|l\|t\|o}] [<params...>]` <br> Flag `+k` - Param: `<key>` <br> Flag `+l` - Param: `<limit>` <br> Flag `(+\|-)o` - Param: `<operatorsNick>` | Edit settings of a channel. <br> `i`: *Invite-only*, `k`: *Access key*, <br> `l`: *User limit*, `t`: *Topic restricted*, <br> `o`: *Channel operators*. |
|   ✅   | [TOPIC](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.4)   | `TOPIC <channel> [<newTopic>]`                   | Get or set the topic. To set a <br> new topic, the user must be a <br> channel operator OR the channel <br> must not have the `+t` option. |
|   ✅   | [INVITE](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.7)  | `INVITE <nick> <channel>`                        | Invite a member on *Invite-Only* <br> channel. The user must be a <br> channel operator. |
|   ✅   | [KICK](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.8)    | `KICK <channel> <nick> [<message>]`              | Kick a member. The user <br> must be a channel operator. |
| &nbsp; |                                                                        |                                                  |             |
|   ✅   | [NAMES](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.5)   | `NAMES [<channel>[,...]]`                        | List all the users on a channel. <br> Operators' nicks are preceded <br> by an `@`. If no arg is given, every <br> channel is listed, and every <br> user without a channel is <br> in an ultimate `*` channel. |
|   ✅   | [LIST](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.6)    | `LIST [<channel>[,...]]`                         | Display the *name*, the amout <br> of *connected users* and <br> the *topic* of the channels <br> (if not specified, every channel). |
| &nbsp; |                                                                        |                                                  |             |
|   ✅   | [PING](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.2)    | `PING *`                                         | Ping. <br> Asking for a Pong. |
|   ✅   | [PONG](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.3)    | `PONG *`                                         | Pong. <br> Asking for a Ping. |

<br>

## Bot's Commands

<br>

| State  | Command |           Usage           | Description |
| ------ | ------- | ------------------------- | ----------- |
|   ✅   | !help   | `!help [<command>]`       | List all available commands <br> or get help for a <br> specific one. |
|   ✅   | !help   | `!join <channel> [<key>]` | Try to join a channel. |
|   ❌   | !help   | `!part <channel>`         | Part from a channel. |
|   ❌   | !help   | `!msg`                    | Start a private conversation. |
|   ✅   | !ping   | `!ping [<whatever>]`      | Ping. <br> Sending Pong. |
|   ✅   | !pong   | `!pong [<whatever>]`      | Ping. <br> Sending Ping. |
|   ✅   | !quote  | `!quote`                  | Display a random quote. <br> API: [Quotable.io](https://api.quotable.io/random) |
|   ✅   | !joke   | `!joke`                   | Display a random joke. <br> API: [ICanHazDadJoke](https://icanhazdadjoke.com/) |
|   ✅   | !fact   | `!fact`                   | Get a random fact about cats. <br> API: [CatFact.ninja](https://catfact.ninja/fact) |
|   ❌   | !help   | `!quit`                   | Quit the server. |

</div>

<br><br>

## Latest 1.7.1: - `major`

<br>

- Clean bot's main.cpp
- [x] INVITE *(fix: channel and nick was inverted)*
- [x] !join - Try to join a channel.
  - Usage: `!join <channel> [<key>]`

<br><br>

## 1.7.0: - `minor`

<br>

- **Norm** *(mandatory part)*
  - Get rid of +200 lines functions
  - Split the code into smaller functions
  - Clean main.cpp
  - Try to not exceed 80 columns (there is some exceptions but..
    it's okay for the lisibility)

<br><br>

## 1.6.6: - `minor`

<br>

- [x] LIST *(fix: topic was not displayed)*
- [x] KICK *(fix: the sender was kicked - instead of the target)*

<br><br>

## 1.6.4: - `major`

<br>

- Error range fixed on the bot.
  - Error range: `[400;599]`
- [x] !quote - Display a random quote.
  - API: [Quotable.io](https://api.quotable.io/random)
- [x] !fact - Get a random fact about cats.
  - API: [CatFact.ninja](https://catfact.ninja/fact)
- [x] **!help** - List all available commands or get help for a specific one.
  - Usage: `!help [<command>]`


<br><br>

## 1.6.0: - `major`

<br>

- **We got the bot into the Internet !** 🌐
- [x] !joke - Display a random joke. (VIA AN API !!! 🤯)
  - *The principle comes from the **microshell** project :*
    *Use an execve to curl the API and get the response.*
  - API: [ICanHazDadJoke](https://icanhazdadjoke.com/api)
  - Other Jokes APIs (maybe for the future if someone is interested):
    - [JokeAPI.dev](https://jokeapi.dev/)
    - [Official-Joke-API of AppSpot.com](https://official-joke-api.appspot.com/jokes/random)
    - [JokeAPI.dev v2](https://v2.jokeapi.dev/joke/Any)
    - [JokeAPI of sv443.net](https://sv443.net/jokeapi/v2/joke/Any)
- Now the bot will not while true when it can't register !


<br><br>

## 1.5.5: - `minor`

<br>

- [x] PRIVMSG *(fix: avoid `ERR_NORECIPIENT` when the user is alone)*
- Individualized `cmdBuffer` for each client (to avoid conflicts when
  receiving messages from multiple clients at the same time)
- Added a protection against a poll error (`POLLERR | POLLHUP | POLLNVAL`)


<br><br>

## 1.5.3: - `major`

<br>

- [x] LIST remake.
- [ ] ~~USERS~~ removed.


<br><br>

## 1.5.1: - `minor`

<br>

- Valgrind cleanup


<br><br>

## 1.5.0: - `major`

<br>

- **IRC Bot !** 🤖
- Command system
- Prefix: `!`
- !!! Multi-threading !!!
  - To be able to get the response of the server / clients while doing the command.
- Commands:
  - Via a completely new parsing and executing way ! (-\_-)
  - [x] `!ping` - Ping. Pong.
  - [x] `!pong` - Pong. Ping.
- Handle elementary commands :
  - [x] `PING` - Ping. Pong.
  - [x] `PONG` - Pong. Ping.
  - [x] `PRIVMSG` - Receive a message.
- Valgrind (of the bot) cleaned !
- Table of bot's commands
- *(I spend at least 20h on this commit... and eventually, I think there is*
  *more lines on the bot than on the mandatory part xD)*


<br><br>

## 1.4.2 - `minor`

<br>

- List | Users | Names command fixed (error when you try to use it before registration)
- Find 2 leaks to fix (check valgrindError.txt)
- Find an IRC client working on 42's pc > [Konversation](https://flathub.org/apps/org.kde.konversation)

<br><br>

## 1.4.1: - `major`

<br>

- [x] LIST command is fixed
- [x] USERS command added
  - Aliases: `users` or `us`

<br><br>

## 1.4.0: - `MAJOR`

<br>

- **IRC Bot !** 🤖
  - `make bonus` to compile the bot.
  - `./ircbot` to run the bot.
  - Usage: `./ircbot <IPv4> <port> [<password>]`
  - On connection, the bot will join the `#bot` channel.
  - Commands: (***MAYBE*** in the future ! We don't know yet, but it's an idea... 🤔)
    - [ ] `!help` - Display the help message.
    - [ ] `!join <channel>` - Join a channel.
    - [ ] `!part <channel>` - Part a channel.
    - [ ] `!weather <city>` - Display the weather of a city.
    - [ ] `!time <city>` - Display the time of a city.
    - [ ] `!stock <symbol>` - Display the stock price of a symbol.
    - [ ] `!quote` - Display a random quote.
    - [ ] `!news` - Display the latest news.
    - [ ] `!joke` - Display a random joke.
    - [ ] `!fact` - Display a random fact.
    - [ ] `!meme` - Display a random meme.
    - [ ] `!msg` - Start a private conversation with the bot.
    - [ ] `!gpt <message>` - Generate a message with GPT-3.
    - [ ] `!quit` - Quit the server.
  - **TODO**:
    - [ ] Response parsing.
      - 'Cause now, if the nick `bot` is already taken, the bot will not work.
      - And, same for the channel `#bot`.
      - So todo: find a solution to this problem.
    - [ ] Commands parsing.
    - [ ] Commands implementation.
    - [ ] And **maybe** try to link the bot to the ✨ Internet ✨.
- New architecture:
  ```tree
  .
  ├── inc
  │   ├── bot
  │   │   ├── bases
  │   │   │   └── *.hpp
  │   │   ├── commands
  │   │   │   └── *.hpp
  │   │   └── bot.hpp
  │   ├── server
  │   │   ├── bases
  │   │   │   └── *.hpp
  │   │   ├── commands
  │   │   │   └── *.hpp
  │   │   └── server.hpp
  │   ├── ft_irc.hpp
  │   ├── IRCException.hpp
  │   └── NumResponses.hpp
  ├── src
  │   ├── bot
  │   │   ├── bases
  │   │   │   └── *.cpp
  │   │   ├── commands
  │   │   │   └── *.cpp
  │   │   └── main.cpp
  │   ├── server
  │   │   ├── bases
  │   │   │   └── *.cpp
  │   │   ├── commands
  │   │   │   └── *.cpp
  │   │   └── main.cpp
  │   └── utils.cpp
  ├── CHANGELOG.md
  └── Makefile
  ```
- Makefile big update *(to compile the serv and the bot)*.


<br><br>

## 1.3.3: - `minor`

<br>

- Getting rid of Channel's `owner` field.
- Now, at the creation of a channel, the creator is automatically added to the `operators` list.


<br><br>

## 1.3.2: - `major`

<br>

- **Hostname for server !** 🏠
- New argument:
  ```usage
  -?, --help                     - display this help
  -h, --hostname  =<hostname>    - hostname (default: 'localhost')
  ```
- Hostname displayed in the server debug (in addition to every other information)
- Since the beginning, the server was sending response with the full identifier
  of the client as prefix (e.g. `:nick!username@host 001 ...`).
- Now, the server sends the correct prefix (e.g. `:hostname 001 ...`).
- *(So, basically, every CPP file has been modified to match the new `Client::send` function... 😅)*


<br><br>

## 1.3.0: - `major`

<br>

- **Password for server !** 🤫
- Arguments parsing:
  ```usage
  Usage: ./ircserv [<params...>]

  Params:
    -h, --help                  - display this help
    -p, --port   =<port>        - port number (default: 8080)
    -k, --key    =<password>    - password for server (default: '')
    -l, --limit  =<clientLimit> - maximum number of clients (default: 100)

  Example: 
  ./ircserv 8080
  ./ircserv 8080 P4ssK3y
  ./ircserv --password=P4ssK3y --limit=50
  ```
- Passwords displayed in the server debug (in addition to the port number and the maximum number of clients)
- [x] **PASS** command

<br><br>

## 1.2.17: - `minor`

<br>

- Keys
  - [x] *now* Limited to 23 characters
  - [x] *now* Must contain at least 1 character
  - [x] *now* Forbidden characters: `,` `:` (+ all whitespaces) (+ all non-printable characters)
- Passwords
  - [x] *now* Limited to 256 characters
  - [x] *now* Must contain at least 1 character
  - [x] *now* Forbidden characters: all whitespaces AND all non-printable characters
- Merge correction (from 1.2.15 commit)

<br><br>

## 1.2.15: - `minor`

<br>

- [ ] LIST (not completed yet)

<br><br>

## 1.2.14: - `major`

<br>

- Channel identifiers
  - [x] Case-insensitive
  - [x] Unique
  - [x] *now* Limited to 50 characters
  - [x] *now* Must contain at least 2 characters
  - [x] Must start with: `#`
  - [x] *now* Forbidden characters: `,` `:` (+ all whitespaces) (+ all non-printable characters)
- Client nicknames
  - [x] Case-insensitive
  - [x] Unique
  - [x] *now* Limited to 9 characters
  - [x] *now* Must contain at least 1 character
  - [x] *now* Allowed characters: letter (`a-z` `A-Z`) digit (`0-9`) `-` `[` `]` `\` `_` `^` `{` `|` `}` ``` ` ```
  - [x] Cannot start with: digit (`0-9`) or `-`
- Client usernames
  - [x] Case-sensitive
  - [x] NOT Unique
  - [x] *now* Limited to 50 characters
  - [x] *now* Must contain at least 1 character
  - [x] *now* Forbidden characters: `,` `:` `!` `@` `*` (+ all whitespaces) (+ all non-printable characters)
- Fix: Command parsing
  - [x] NPrefix handled
  - [x] Empty trailing handled
  - [x] Quotes not needed --> no longer handled


<br><br>

## 1.2.12: - `major`

<br>

- [x] NAMES

<br><br>

## 1.2.11: - `major`

<br>

- [x] KICK

<br><br>

## 1.2.10: - `minor`

<br>

- Deconnection when not registered.
  - There was an infinite loop.
  - Now, the `QUIT` command works even if the user is not registered.
- Arguments parsing.
  - Now, we can specify the port number and the maximum number of clients.
  - `./ircserv [<port> [<maxClients>]]`
  - `port` ∈ [1, 65535] (default: 8080)
  - `maxClients` ∈ [1, 65535] (default: 100)
- Port number and max clients number are now displayed in the server debug.

<br><br>

## 1.2.9: - `major`

<br>

- [x] INVITE
- [x] JOIN *(fix: remove user from invite list on join)*
- [x] MODE *(fix: clear invite list on `-i`)*

<br><br>

## 1.2.8: - `major`

<br>

- [x] TOPIC

<br><br>

## 1.2.6: - `minor`

<br>

- Nicknames are now case-insensitive (--> Update of the `NICK` command)
- Channel names are now case-insensitive

<br><br>

## 1.2.5: - `major`

<br>

- [x] MODE  -->  Only for channels
- [x] PRIVMSG *(fix: don't broadcast to sender on channel)*
- Topic restriction on by default
- Proper exit on connection lost (e.g. `SIGINT`, `SIGKILL`, simple close, etc.)
- Changelog update: Commands table !

<br><br>

## 1.2.0 - `major`

<br>

&nbsp; &nbsp; &nbsp; ================== &nbsp; &nbsp; &nbsp;<br>
&nbsp; &nbsp; &nbsp; **| &nbsp; ~ &nbsp; Channels ! &nbsp; ~ &nbsp; |** &nbsp; &nbsp; &nbsp;<br>
&nbsp; &nbsp; &nbsp; ================== &nbsp; &nbsp; &nbsp;

> Finally, we have channels ! 🎉
> *(It was a looong way to get here because of the RFC doc but... now we have it !)*

- [x] PRIVMSG
- [x] JOIN
- [x] PART
- [x] QUIT *(fix: send only to the current channels)*
- Numeric replies refactoring
- Commands logging update
- Changlog organisation update

<br><br>

## 1.1.1 - `minor`

<br>

- Fixed commands:
  - [x] NICK
  - [x] QUIT
- Makefile update (now runnable)

<br><br>

## 1.1.0 - `major`

<br>

- NumResponses.hpp (**[RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812#section-5)**
  *[old: [RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459#section-6)]*)
- Better parsing ([Message format in 'pseudo' BNF](https://datatracker.ietf.org/doc/html/rfc1459#section-2.3.1)
  and [Message format in Augmented BNF](https://datatracker.ietf.org/doc/html/rfc2812#section-2.3.1))
- Commands:
  - [x] NICK
  - [x] USER
  - [x] PING
  - [x] PONG
  - [ ] ~~QUIT~~
- Registration (welcome message, etc.)
- Prefixes are now fixed (syntax: `:prefix COMMAND params`)
- Now, I understand the IRC protocol better... _(kinda) 😅_
- And the last but not the least: **I understood how to read the RFC man pages.. (It was a hard time but, it seems to be okay now. I guess it was worth it.)**

<br><br>

## 1.0.3 - `minor`

<br>

- Fix changelog file

<br><br>

## 1.0.2 - `major`

<br>

- Commands Introduction
- NickCommand
- UserCommand
- Utils client functions (ex: sendCommand)
- Class Channel (useless for now)
- File organisation
- New Display (Server debug)
- Changelog file

<br><br>

## First: 1.0.0 - `major`

<br>

- Implementing bases
- Server & Client:
  - Binding
  - Listening
  - Accepting
  - Simple communication (recv/send)


<div align="right">
  <br><br>

  ---

  See yall ! 😉
  > — &nbsp;&nbsp; _[Luzog78](https://github.com/Luzog78)_ &nbsp; | &nbsp; _[ysabik](https://profile.intra.42.fr/users/ysabik)_
</div>
