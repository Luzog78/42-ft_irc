<div align="center">

# Changelog of ft_irc

<br>

|           Version            |       Tag        | Importance | Runnable |
| ---------------------------- | ---------------- | ---------- | -------- |
| [1.2.6](#latest-126---minor) |      Latest      |  `minor`   |    ✅    |
| [1.2.5](#125---major)        |       MODE       |  `major`   |    ✅    |
| [1.2.0](#120---major)        |     Channels     |  `major`   |    ✅    |
| [1.1.1](#111---minor)        |                  |  `minor`   |    ✅    |
| [1.1.0](#110---major)        |     Commands     |  `major`   |    ❌    |
| [1.0.3](#103---minor)        |                  |  `minor`   |    ✅    |
| [1.0.2](#102---major)        |                  |  `major`   |    ✅    |
| [1.0.0](#first-100---major)  |     Initial      |  `major`   |    ✅    |

<br><br>

| State  |                                Command                                 |                      Usage                       | Description |
| ------ | ---------------------------------------------------------------------- | ------------------------------------------------ | ----------- |
|   ✅   | [USER](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.3)    | `USER <username> * * <realname>`                 | **Needed to register.** <br> Setup username and real name. |
|   ✅   | [NICK](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.2)    | `NICK <nickname>`                                | **Needed to register.** <br> Setup or change nickname. <br> The nickname MUST be UNIQUE. |
|   ❌   | [PASS](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.1)    |                                                  |             |
|   ✅   | [QUIT](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.6)    | `QUIT [<message>]`                               | Disconnect properly, informing the <br> other clients, leaving channels. |
| &nbsp; |                                                                        |                                                  |             |
|   ✅   | [JOIN](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.1)    | `JOIN <channels>[,...] <keys>[,...]`             | Join channels, using keys if <br> necessary. The channel's names <br> MUST start with a hash (`#`) |
|   ✅   | [PART](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.2)    | `PART <channels>[,...] [<message>]`              | Quit properly channels, informing <br> the other clients, closing <br> channels if empty. |
|   ✅   | [PRIVMSG](https://datatracker.ietf.org/doc/html/rfc1459#section-4.4.1) | `PRIVMSG <receivers>[,...] <message>`            | Send a message. Receiver is either <br> **a user** or **a channel (#...)**. No <br> message should be sent to the <br> sender *(except when it is part <br> of the receivers)*. |
| &nbsp; |                                                                        |                                                  |             |
|   ✅   | [MODE](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.3)    | `MODE <channel> [[+\|-]{i\|k\|l\|t\|o}] [<params...>]` <br> Flag `+k` - Param: `<key>` <br> Flag `+l` - Param: `<limit>` <br> Flag `(+\|-)o` - Param: `<operatorNick>` | Edit settings of a channel. <br> `i`: *Invite-only*, `k`: *Access key*, <br> `l`: *User limit*, `t`: *Topic restricted*, <br> `o`: *Channel operators*. |
|   ❌   | [TOPIC](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.4)   |                                                  |             |
|   ❌   | [INVITE](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.7)  |                                                  |             |
|   ❌   | [KICK](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.8)    |                                                  |             |
| &nbsp; |                                                                        |                                                  |             |
|   ❌   | [NAMES](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.5)   |                                                  |             |
|   ❌   | [LIST](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.6)    |                                                  |             |
|   ❌   | [USERS](https://datatracker.ietf.org/doc/html/rfc1459#section-5.5)     |                                                  |             |
| &nbsp; |                                                                        |                                                  |             |
|   ✅   | [PING](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.2)    | `PING *`                                         | Ping. <br> Asking for a Pong. |
|   ✅   | [PONG](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.3)    | `PONG *`                                         | Pong. <br> Asking for a Ping. |

</div>

<br>

## Latest 1.2.6: - `minor`

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
