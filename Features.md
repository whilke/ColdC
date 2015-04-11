# Features #

The Cold Project manages evolution and development of ColdC and Genesis, a ColdC driver. ColdC is an Object Oriented database server language originally engineered by Greg Hudson with influences from C, MOO and CoolMUD.


## Disk based database ##

Because the database is disk based, only the currently active objects will be in memory. This means you driver will not bloat into large virtual memory pages.

## Efficient interpreter ##

The interpreter for ColdC is engineered for speed by using abstract representations of data (hashes) rather than manipulating string after string directly.

## Easily Extendable ##

Genesis allows for additions of Native Methods to objects through a simple module system. This means you can optimize your database as needed. Furthermore, it also allows for easy additions of new data types.

## Multiple Inheritance ##

ColdC allows for multiple parents per object.

## Powerful Networking ##

ColdC gives the ability to easily handle multiple incoming and outgoing connections. You are not restricted to a single connection port--instead you can have multiple ports for each service.

## Language Encapsulation ##

ColdC has a high defined role for data encapsulation and modularity.

## Server Role Abstraction ##

The server does not try to manage your database, it simply interprets ColdC. It does not handle permissions, command parsing nor anything else. It simply knows of a connection and sends the input and output to and from the connection respectively. Because of this the same driver has successfully been used to write MUDs and dynamic WWW servers.

## Asynchronous Backups ##

Database backups are done asyncronously, while your system is still functioning as normal.

## Dynamic Text ##

ColdCore defines ctext which is an internal abstraction of text. Using ctext ColdCore can quickly parse a document to HTML, Plain-Text or any other text format you desire.

## Multi-Platform Support ##

Genesis compiles with ease on nearly all modern unix and Win32 systems.