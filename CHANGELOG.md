<div align="center">

# Changelog of ft_irc

<br>

|            Version             |       Tag        | Importance | Runnable |
| ------------------------------ | ---------------- | ---------- | -------- |
| [1.2.17](#latest-1217---minor) |      Latest      |  `minor`   |    ✅    |
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

<br><br>

| State  |                                Command                                 |                      Usage                       | Description |
| ------ | ---------------------------------------------------------------------- | ------------------------------------------------ | ----------- |
|   ✅   | [USER](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.3)    | `USER <username> * * <realname>`                 | **Needed to register.** <br> Setup username and real name. |
|   ✅   | [NICK](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.2)    | `NICK <nickname>`                                | **Needed to register.** <br> Setup or change nickname. <br> The nickname MUST be UNIQUE. |
|   ❌   | [PASS](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.1)    |                                                  |             |
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
|   🟠   | [LIST](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.6)    | `LIST [<channel>[,...]]`                         |             |
|   ❌   | [USERS](https://datatracker.ietf.org/doc/html/rfc1459#section-5.5)     |                                                  |             |
| &nbsp; |                                                                        |                                                  |             |
|   ✅   | [PING](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.2)    | `PING *`                                         | Ping. <br> Asking for a Pong. |
|   ✅   | [PONG](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.3)    | `PONG *`                                         | Pong. <br> Asking for a Ping. |

</div>

<br>

## Latest 1.2.17: - `minor`

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
