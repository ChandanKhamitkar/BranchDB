import { onest } from "../layout";
import { MdContentCopy } from "react-icons/md";
import { IoLogoGithub } from "react-icons/io5";

const sdkCardData = [
    {
        title: "Seamless Integration",
        desc: "Install with a single command via npm. Connect to your database and perform operations with a clean, promise-based API.",
        imageLink: "yellow-integration.png"
    },
    {
        title: "Ultra-Lightweight",
        desc: "With zero external dependencies, the SDK is fast, tiny, and focuses purely on efficient network communication.",
        imageLink: "yellow-lightweight.png"
    },
    {
        title: "Protocol-Aware",
        desc: "The SDK handles all binary serialization, deserialization, and authentication handshakes, so you can focus on your data, not on the protocol.",
        imageLink: "yellow-aware.png"
    },
]

export default function Page() {
    return (
        <div className={`h-screen w-full bg-black flex flex-col overflow-x-hidden overflow-y-scroll rounded-md relative pt-[130px] ${onest.className} pb-8 custom-scrollbar`}>

            <img src="js-sdk-hero-card.png" alt="Javascript SDK hero card" className="w-3/4 rounded-2xl mx-auto" />

            <div className="w-fit mx-auto flex justify-center items-center gap-10 mt-6 bg-neutral-100/10 backdrop-blur-2xl rounded-md text-md md px-4 py-3 font-mono">
                <span >npm i branchdb-client</span>
                <MdContentCopy className="text-neutral-500 cursor-pointer hover:text-neutral-50 text-lg" />
            </div>

            <div className="flex justify-center items-center mt-12 h-max gap-8">
                {
                    sdkCardData.map((item, index) => <div key={index} className="bg-white/5 flex flex-col justify-center items-start rounded-2xl border border-white/10 w-96 overflow-clip h-full hover:border-jsyellow/60">
                        <img src={item.imageLink} alt="Integration Crad Img" className="w-full object-cover" />
                        <div className="bg-black px-5 py-6 w-full h-full">
                            <p className="text-xl text-white font-medium">{item.title}</p>
                            <p className="text-neutral-500 text-wrap text-md mt-2">{item.desc}</p>
                        </div>
                    </div>)
                }
            </div>

            {/* Github Repo Promotion */}
            <div className="flex flex-col justify-center items-center mx-auto mt-12 text-center">
                <p className="text-4xl font-bold text-white">
                    Want to Unleash Full Power?
                </p>
                <p className="text-md font-base text-neutral-400 mt-4">
                    Clone the source code. You're the architect—build it, run it, be in charge.
                </p>
                <a
                    href="https://github.com/ChandanKhamitkar/BranchDB"
                    target="_blank"
                    rel="noopener noreferrer"
                    className="relative inline-flex h-fit overflow-hidden rounded-xl p-[3px] mt-6 cursor-pointer"
                >
                    <span className="absolute inset-[-1000%] animate-[spin_2s_linear_infinite] bg-[conic-gradient(from_90deg_at_50%_50%,#ff0000_0%,#ff7f00_16%,#ffff00_33%,#00ff00_50%,#0000ff_66%,#8b00ff_83%,#ff0000_100%)]" />

                    <span className="inline-flex h-full w-full items-center justify-center rounded-xl bg-white/90 px-6 py-4 text-lg font-medium text-gray-900 backdrop-blur-xl">
                        Download Source Code
                        <IoLogoGithub className="text-gray-900 size-9 ml-4" />
                    </span>
                </a>



            </div>


        </div>
    );
};
