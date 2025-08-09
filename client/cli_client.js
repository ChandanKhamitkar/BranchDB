import net from "net";
import readline from "readline";

const TOKEN = "radheradhee";
const PAYLOAD_TYPE = {
  MONOSTATE: 0,
  STRING: 1,
  VECTOR_STRING: 2,
};

const HOST = "localhost";
const PORT = 1981;

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  prompt: "> ",
});

const client = new net.Socket();

client.on("connect", () => {
  console.log("CLIENT connected to server at ", HOST, " ", PORT);
  console.log("CLIENT Ready to send commands. Type 'exit' to quit.");

  // const auth_payload = "AUTH" + TOKEN;
  // client.write(auth_payload + '\n');

  rl.prompt();
});

client.on("data", (data) => {
  // console.log(`\n[RAW DATA] Received ${data.length} bytes:`);
  // console.log(`[RAW DATA] Hex: ${data.toString("hex")}`);

  let offset = 0;

  const status_code = data.readUint32LE(offset);
  offset += 4;

  const success = data.readInt8(offset);
  offset += 1;

  const message_len = data.readUint32LE(offset);
  offset += 4;

  const message = data.toString("utf8", offset, offset + message_len);
  offset += message_len;

  const payload_type = data.readInt8(offset);
  offset += 1;

  let payload;

  if (payload_type === PAYLOAD_TYPE.MONOSTATE) {
    payload = null;
  } else if (payload_type === PAYLOAD_TYPE.STRING) {
    const payload_len = data.readUint32LE(offset);
    offset += 4;
    payload = data.toString("utf8", offset, offset + payload_len);
    offset += payload_len;
  } else if (payload_type === PAYLOAD_TYPE.VECTOR_STRING) {
    const vector_size = data.readUint32LE(offset);
    offset += 4;

    const string_array = [];
    for (let i = 0; i < vector_size; i++) {
      const str_len = data.readUInt32LE(offset);
      offset += 4;

      const str = data.toString("utf8", offset, offset + str_len);
      offset += str_len;
      string_array.push(str);
    }
    payload = string_array;
  }

  const response = {
    statusCode: status_code,
    success: success,
    message: message,
    payloadType: payload_type,
    payload: payload,
  };

  console.log(`[PARSED] Received Response:`, response);

  rl.prompt();
});

rl.on("line", (line) => {
  const trimmedLine = line.trim();
  if (trimmedLine.toLowerCase() === "exit") {
    console.log("[CLIENT] Closing connection...");
    client.end();
    rl.close();
  } else {
    client.write(trimmedLine + '\n');
  }
});

client.on("close", () => {
  console.log("CLIENT connection closed.");
  exit(0);
});

client.on("error", (err) => {
  console.log("CLIENT error occured: ", err);
  rl.close();
});

client.connect(PORT, HOST, () => {});
