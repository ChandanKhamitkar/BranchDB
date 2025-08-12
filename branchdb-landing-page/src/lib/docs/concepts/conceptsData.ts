export const commandsData = [
    {
        command: 'SET',
        syntax: 'SET <key> <value> [EX <seconds>]',
        description: 'Sets a key to hold a string value, with an optional Time-to-Live (TTL) in seconds.'
    },
    {
        command: 'GET',
        syntax: 'GET <key>',
        description: 'Retrieves the value of a key from the database.'
    },
    {
        command: 'DEL',
        syntax: 'DEL <key>',
        description: 'Deletes a specified key from the database.'
    },
    {
        command: 'EXISTS',
        syntax: 'EXISTS <key>',
        description: 'Checks for the existence of a key in the database, returning a boolean value.'
    },
    {
        command: 'TTL',
        syntax: 'TTL <key>',
        description: 'Returns the remaining time to live (in seconds) for a key with an expiry set.'
    },
    {
        command: 'EXPIRE',
        syntax: 'EXPIRE <key> <seconds>',
        description: 'Sets a new TTL for an existing key, overwriting any previous expiry.'
    },
    {
        command: 'PERSIST',
        syntax: 'PERSIST <key>',
        description: 'Removes the TTL from a key, making it permanent.'
    },
    {
        command: 'GETALL',
        syntax: 'GETALL',
        description: 'Returns all keys for the authenticated user\'s data partition.'
    },
    {
        command: 'FLUSH',
        syntax: 'FLUSH',
        description: 'Deletes all keys for the authenticated user and compacts the log file.'
    }
];

export const TTLTerminalLines = [
    {
        parts: [
            { text: '> ', color: 'white' },
            { text: 'SET ', color: 'text-pink-500' },
            { text: 'X 6 ', color: 'text-blue-500' },
            { text: 'EX 10', color: 'text-green-500' }
        ]
    },
    {
        parts: [
            { text: '> ', color: 'white' },
            { text: 'GET ', color: 'text-pink-500' },
            { text: 'X', color: 'text-blue-500' }
        ]
    },
    { parts: [{ text: '10', color: 'text-yellow-400' }] },
    { parts: [{ text: '// After 10 Seconds', color: 'text-neutral-400' }] },
    {
        parts: [
            { text: '> ', color: 'white' },
            { text: 'GET ', color: 'text-pink-500' },
            { text: 'X', color: 'text-blue-500' }
        ]
    },
    {
        className: 'flex justify-start items-start gap-2 text-wrap', parts: [
            { text: 'Key Not found', color: 'text-yellow-400 text-wrap' },
            { text: "// Key 'X' Expired ( Deleted by Background Thread )", color: 'text-neutral-400 text-wrap' }
        ]
    }
];