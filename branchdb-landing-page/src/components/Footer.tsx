import { onest } from "@/app/layout";

export default function Footer() {
    const linkSections = [
        {
            title: "Links",
            items: ["Github", "Developer"],
        },
        {
            title: "Docs",
            items: ["Getting Started", "Core Features", "Client SDK's"],
        },
        {
            title: "SDK",
            items: ["JavaScript SDK"],
        },
    ];

    return (
        <div className={`bg-black flex flex-col justify-between items-center w-full h-screen ${onest.className} overflow-clip z-10 relative pb-10`}>
            <img src="line1-footer.svg" alt="Line" className="absolute top-0 left-0 h-3/4" />
            <img src="line2-footer.svg" alt="Line" className="absolute bottom-0 right-0 h-[60%]" />
            <div className="absolute top-0 right-0 translate-x-1/2 -translate-y-1/2 w-[800px] h-[600px] rounded-full bg-gradient-to-b from-[#FE6A00] to-[#FE6A00]/[20%] opacity-75 blur-[250px]"></div>
            <div className="absolute bottom-0 left-0 -translate-x-1/2 translate-y-1/2 w-[500px] h-[300px] rounded-full bg-gradient-to-b from-[#FE6A00] to-[#FE6A00]/[20%] opacity-75 blur-[250px]"></div>

            {/* Background giant text */}
            <p className="font-medium text-[250px] bg-gradient-to-b from-white via-[#CCCCCC]/[50%] to-[#999999]/0 text-transparent bg-clip-text opacity-10 z-20">BranchDB</p>

            <div className="flex flex-col justify-end items-center w-full z-20">
                {/* Main Content */}
                <div className="w-full flex justify-between items-start px-12">
                    <div>
                        {/* Brand name */}
                        <p className="font-semibold text-5xl text-neutral-400">BranchDB</p>
                        <p className="font-light text-lg text-neutral-500 mt-2">A durable, in-memory database built in C++.</p>
                    </div>

                    {/* Links */}
                    <div className="flex justify-around items-start space-x-12 text-neutral-500">
                        {linkSections.map((section) => (
                            <div key={section.title} className="flex flex-col space-y-3">
                                <p className="font-semibold underline underline-offset-4 text-xl">{section.title}</p>
                                {section.items.map((link) => (
                                    <a key={link} className="text-base hover:text-white transition">{link}</a>
                                ))}
                            </div>
                        ))}
                    </div>
                </div>
                
                {/* Divider */}
                <div className="w-3/4 h-px bg-neutral-700 rounded-full my-8"></div>

                {/* Copyright */}
                <p className="font-normal text-neutral-500 text-sm">© 2025 BranchDB — Built with C++ | KHAMITKAR SAI CHANDAN</p>
            </div>
        </div>
    );
}