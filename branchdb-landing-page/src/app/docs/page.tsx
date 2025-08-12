import CodeBlock from "@/components/docs/CodeBlock";
import Line from "@/components/docs/Line";
import DocsLayout from "./DocsLayout";
import SubHeadLine from "@/components/docs/SubHeadLine";
import Point from "@/components/docs/Point";

export default function Page() {
    return (
        <DocsLayout>
            <div className="w-full h-auto flex flex-col justify-start items-start">

                {/* WelCome Card */}
                <div className="w-full h-fit relative px-4 py-6 rounded-xl overflow-clip">
                    <div className="flex flex-col">
                        {/* Docs Title */}
                        <span className="inline-block text-4xl font-bold leading-dense text-transparent md:text-4xl lg:text-5xl xl:text-6xl z-20 drop-shadow-2xl"
                            style={{
                                backgroundImage: 'linear-gradient(143.14deg, #e0cc9f 49.06%, rgba(189,157,79,0) 91.07%)',
                                WebkitBackgroundClip: 'text',
                                backgroundClip: 'text',
                            }}>
                            Docs
                        </span>

                        <span className="text-14 font-medium leading-snug -tracking-tighter drop-shadow-2xl md:text-left md:text-16 md:font-normal lg:text-18 z-20 mt-4 ml-1"
                            style={{
                                backgroundImage: 'linear-gradient(143.14deg, #e0cc9f 49.06%, rgba(189,157,79,0) 91.07%)',
                                WebkitBackgroundClip: 'text',
                                backgroundClip: 'text',
                            }}
                        >
                            Welcome to the official documentation for Branch DB
                        </span>
                    </div>

                    {/* <div className="absolute inset-0 z-0 bg-[#2E2A26]"></div> */}
                    <img src="/Gold.svg" alt="Gold" className="absolute inset-0 w-full blur-2xl" />
                    <div className="w-6 h-6 bg-noise absolute inset-0 z-10 opacity-30 [mask-image:linear-gradient(0,#D9D9D9_0%,rgba(115,115,115,0.00)_100%)]"></div>


                </div>

                {/* #docs */}
                <div className="w-full p-4 mt-6">
                    <p className="text-4xl font-bold text-white mb-4">Getting Started</p>
                    <Point pt="Before you start using Branch DB, you need to install it for your own operating system." />
                    <Point pt="We provide a Docker image for easy deployment or you can build it from source." />

                    <SubHeadLine id="installation" headline="Installation & Setup" />
                    <Point pt="Our recommended approach is to use the official Docker image. This handles all C++ build steps and dependencies for you." />

                    <p className="mt-8 mb-4 text-xl underline underline-offset-8 font-medium decoration-neutral-700/50">Option A: Docker (Recommended)</p>
                    <Point pt="You can pull the pre-built image from Docker Hub and run it directly." />
                    <CodeBlock num="1" step="Pull the Image:" code="> docker pull chandankhamitkar/branchdb" />
                    <CodeBlock num="2" step="Run the Container:" code="> docker run -p 1981:1981 chandankhamitkar/branchdb" />

                    <p className="mt-8 mb-4 text-xl underline underline-offset-8 font-medium decoration-neutral-700/50">Option B: Build from Source</p>
                    <Point pt="If you prefer to build the database from source, you will need a C++ toolchain and CMake installed." />
                    <CodeBlock step="Clone the Repository:"
                        code={["git clone https://github.com/ChandanKhamitkar/BranchDB.git", "cd BranchDB"]}
                    />

                    <Line customStyling="mt-7" />

                    <SubHeadLine id="quickstart" headline="Quickstart" />
                    <CodeBlock step="Build and Run:"
                        code={["mkdir build", "cd build", "cmake ..", "cmake --build .", "cd Debug", "./BranchDB.exe"]}
                    />

                    <p className="mt-8 mb-4 text-xl uppercase font-medium decoration-neutral-700/50">OR</p>

                    <CodeBlock step="If you are on BASH/UNIX terminal, directly run"
                        code={"./branchdb-run.sh"}
                    />
                    <Point pt="By default, Branch DB starts on port 1981." customStyling="mt-4" />
                    <Point pt="Once the server is running on localhost:1981, you can connect using any TCP client or directly run commands via CLI." customStyling="mt-4" />

                    <CodeBlock step="Example session with telnet:"
                        code={["$ telnet localhost 1981",
                            "> AUTH RadheKrishn",
                            "OK AUTH",
                            "> SET mykey value",
                            "[OK] SET",
                            "> GET mykey",
                            "[OK] GET: key mykey -> value",
                        ]}
                    />
                </div>
            </div>
        </DocsLayout>
    );
}

