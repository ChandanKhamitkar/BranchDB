import CodeBlock from "@/components/docs/CodeBlock";
import SubHeadLine from "@/components/docs/SubHeadLine";
import Line from "@/components/docs/Line";
import DocsLayout from "../DocsLayout";
import Point from "@/components/docs/Point";
import CommandsTable from "@/components/docs/CommandsTable";
import { MdContentCopy } from "react-icons/md";
import CodeSnippet from "@/components/docs/CodeSnippet";
import SyntaxHighlighter from "@/components/docs/SyntaxHighlighter";
import { methodsData, ServerResponseSample, ServerResponseTypes } from "@/lib/docs/sdk/sdkData";


export default function page() {
    return (
        <DocsLayout>
            <div className="w-full h-auto flex flex-col justify-start items-start">

                {/* SDK's */}
                <div className="w-full p-4 mt-6">
                    <p className="text-4xl font-bold text-white mb-4">Client SDK - TypeScript/JavaScript</p>
                    <Point pt="We provide an official client SDK for Node.js, which simplifies network communication and protocol handling." />
                    <Point pt="Below is hands-on walkthrough of all the list of asynchronous methods that BranchDB Client SDK provides." />

                    <SubHeadLine headline="Client Methods | This is all what you need" />

                    <CommandsTable heads={[{ cnt: "Method", gradientMode: false }, { cnt: "Description", gradientMode: false }]} data={methodsData} />

                    <SubHeadLine headline="Install" />
                    <CodeBlock step="To install branchdb-client, run:" code="npm i branchdb-client" />

                    <SubHeadLine headline="Connect and Test" />
                    <Point pt="Connect to localhost on port 1981." />

                    <SyntaxHighlighter
                        code={
                            `import { Branch } from "branchdb-client";

const config = {
  host: process.env.BRANCH_DB_HOST || "localhost",
  port: parseInt(process.env.BRANCH_DB_PORT || "1981"),
  username: "ChandanKhamitkar-Project",
  token: process.env.BRANCH_DB_TOKEN"
};

const client = new Branch(config);

await client.connect();
`
                        }
                    />

                    <Point pt="Example usage of as all methods mentioned above" customStyling="mt-6" />
                    <SyntaxHighlighter
                        code={
`// Store a token or username or anything
const Response = await client.set("token", "Chandan");

// Store username with Time limit expiry of 30 seconds
const Response = await client.set("user202", {name: "Chandan", age: 21}, 30);

// Fetch stored name via key
const Response = await client.get("user:101");

// Delete stored token
const Response = await client.del("token");

// Check if token exists or not
const Response = await client.exists("token");
// Success response = 'true' if key exists, else 'false'

// Get the remaining time left for key in seconds.
const Response = await client.ttl("token");

// Reset the expiry time for token to 120 seconds.
const Response = await client.expire("token", 120);

// Remove expiry time for token. Make it no-expriy key.
const Response = await client.persist("token");

// Get list of all keys exist in database. 
const Response = await client.getall();
// payload : ['A', 'B', 'C', 'D']

// Delete all keys in database.
const Response = await client.flush();

// Terminate client connection with server.
const Response = await client.disconnect();

`
                        }
                    />

                    <SubHeadLine headline="We also provide Better Response for every method you call." />
                    <CodeSnippet title="Terminal" lines={ServerResponseSample} />

                    <Point pt="Below is the better understanding of response Types." customStyling="mt-6" />
                    <CodeSnippet title="Terminal" lines={ServerResponseTypes} />
                </div>
            </div>
        </DocsLayout>
    )
};
