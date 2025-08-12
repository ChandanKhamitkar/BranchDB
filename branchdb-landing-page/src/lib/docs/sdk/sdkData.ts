export const methodsData = [
  {
    syntax: "connect()",
    description: "Establishes a connection with the server.",
  },
  {
    syntax: "set(key, value, ttl?)",
    description: "Sets a key-value pair, with an optional TTL in seconds.",
  },
  {
    syntax: "get(key)",
    description: "Retrieves the value for a given key.",
  },
  {
    syntax: "del(key)",
    description: "Deletes a key-value pair.",
  },
  {
    syntax: "exists(key)",
    description: "Checks if a key exists.",
  },
  {
    syntax: "ttl(key)",
    description: "Returns the remaining time to live for a key.",
  },
  {
    syntax: "expire(key, ttl)",
    description: "Sets a new TTL for an existing key.",
  },
  {
    syntax: "persist(key)",
    description: "Removes the TTL from a key.",
  },
  {
    syntax: "getall()",
    description: "Returns a list of all keys in the database.",
  },
  {
    syntax: "flush()",
    description: "Deletes all keys from the database.",
  },
  {
    syntax: "disconnect()",
    description: "Terminates the Session TCP connection with BranchDB server.",
  },
];

export const ServerResponseSample = [
  {
    parts: [{ text: "{", color: "text-pink-500" }],
  },
  {
    parts: [
      { text: "\tstatusCode ", color: "text-pink-500" },
      { text: ": ", color: "white" },
      { text: "200", color: "text-green-500" },
    ],
  },
  {
    parts: [
      { text: "\tsuccess ", color: "text-pink-500" },
      { text: ": ", color: "white" },
      { text: "true", color: "text-green-500" },
    ],
  },
  {
    parts: [
      { text: "\tmessage ", color: "text-pink-500" },
      { text: ": ", color: "white" },
      { text: "Successfully Authenticated.", color: "text-green-500" },
    ],
  },
  {
    parts: [
      { text: "\tpayload ", color: "text-pink-500" },
      { text: ": ", color: "white" },
      { text: "Here is your token: 833ca2ed8d167", color: "text-green-500" },
    ],
  },
  {
    parts: [{ text: "}", color: "text-pink-500" }],
  },
];

export const ServerResponseTypes = [
  {
    parts: [{ text: "{", color: "text-pink-500" }],
  },
  {
    parts: [
      { text: "\tstatusCode ", color: "text-pink-500" },
      { text: ": ", color: "white" },
      { text: "number", color: "text-green-500" },
    ],
  },
  {
    parts: [
      { text: "\tsuccess ", color: "text-pink-500" },
      { text: ": ", color: "white" },
      { text: "boolean", color: "text-green-500" },
    ],
  },
  {
    parts: [
      { text: "\tmessage ", color: "text-pink-500" },
      { text: ": ", color: "white" },
      { text: "string", color: "text-green-500" },
    ],
  },
  {
    parts: [
      { text: "\tpayload ", color: "text-pink-500" },
      { text: ": ", color: "white" },
      { text: "string | string[] | null", color: "text-green-500" },
    ],
  },
  {
    parts: [{ text: "}", color: "text-pink-500" }],
  },
  {
    parts: [{ text: " ", color: "white" }],
  },
  {
    parts: [{ text: "// StatuCodes: ", color: "text-neutral-400" }],
  },
  {
    parts: [
      {
        text: "// 200 -> On Successfull operation.",
        color: "text-neutral-400",
      },
    ],
  },
  {
    parts: [
      { text: "// 400 -> Invalid Input from user.", color: "text-neutral-400" },
    ],
  },
  {
    parts: [
      { text: "// 404 -> Eg: Key not found.", color: "text-neutral-400" },
    ],
  },
  {
    parts: [
      {
        text: "// 500 -> Server implementation error | Server crash.",
        color: "text-neutral-400",
      },
    ],
  },
  {
    parts: [{ text: " ", color: "white" }],
  },
  {
    parts: [
      {
        text: "// Success is 'true' only if StatuCode = 200",
        color: "text-neutral-400",
      },
    ],
  },
  {
    parts: [{ text: " ", color: "white" }],
  },
  {
    parts: [
      {
        text: "// Payload:",
        color: "text-neutral-400",
      },
    ],
  },
  {
    parts: [
      {
        text: "// Will be NULL for most of operations except these methods -> AUTH | GET | GETALL",
        color: "text-neutral-400",
      },
    ],
  },
];
