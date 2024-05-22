<div align="center">

# Changelog of ft_irc

<br>

|           Version            |       Tag        | Importance | Runnable |
| ---------------------------- | ---------------- | ---------- | -------- |
| [1.2.0](#latest-120---major) | Latest, Channels |  `major`   |    ✅    |
| [1.1.1](#111---minor)        |                  |  `minor`   |    ✅    |
| [1.1.0](#110---major)        |     Commands     |  `major`   |    ❌    |
| [1.0.3](#103---minor)        |                  |  `minor`   |    ✅    |
| [1.0.2](#102---major)        |                  |  `major`   |    ✅    |
| [1.0.0](#first-100---major)  |     Initial      |  `major`   |    ✅    |

</div>

<br>

## Latest: 1.2.0 - `major`

<br>

&nbsp; &nbsp; &nbsp; __~ &nbsp; Channels ! &nbsp; ~__ &nbsp; &nbsp; &nbsp;

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
