import { onest } from "@/app/layout";
import { linkSections } from "@/lib/footer";

export default function Footer() {
  return (
    <footer
      className={`
        relative bg-black ${onest.className} overflow-clip z-10 flex flex-col min-h-[60vh] md:min-h-[70vh] lg:h-screen
      `}
    >
      {/* Decorative lines */}
      <img
        src="line1-footer.svg"
        alt=""
        aria-hidden="true"
        className="pointer-events-none select-none absolute top-0 left-0 h-1/3 sm:h-1/2 lg:h-3/4"
      />
      <img
        src="line2-footer.svg"
        alt=""
        aria-hidden="true"
        className="pointer-events-none select-none absolute bottom-0 right-0 h-1/4 sm:h-1/3 lg:h-[60%]"
      />

      {/* Glows */}
      <div
        className="
          absolute top-0 right-0 translate-x-1/2 -translate-y-1/2 w-[340px] h-[260px] sm:w-[520px] sm:h-[380px] lg:w-[800px] lg:h-[600px] rounded-full bg-gradient-to-b from-[#FE6A00] to-[#FE6A00]/20 opacity-75 blur-[120px] sm:blur-[180px] lg:blur-[250px]
        "
      />
      <div
        className="
          absolute bottom-0 left-0 -translate-x-1/2 translate-y-1/2 w-[260px] h-[160px] sm:w-[380px] sm:h-[220px] lg:w-[500px] lg:h-[300px] rounded-full bg-gradient-to-b from-[#FE6A00] to-[#FE6A00]/20 opacity-75 blur-[120px] sm:blur-[180px] lg:blur-[250px]
        "
      />

      {/* Background word */}
      <p
        className="
          pointer-events-none select-none absolute inset-x-0 mx-auto text-center z-20 font-medium text-[clamp(6rem,18vw,15rem)] bg-gradient-to-b from-white via-[#CCCCCC]/50 to-[#999999]/0 text-transparent bg-clip-text opacity-10 top-[10%] sm:top-[8%] lg:top-[6%]
        "
      >
        BranchDB
      </p>

      {/* Content */}
      <div
        className="
          relative z-20 mx-auto max-w-7xl px-4 sm:px-6 lg:px-12 pt-24 sm:pt-32 lg:pt-8 pb-10 w-full mt-auto
        "
      >
        {/* Header row */}
        <div
          className="
            w-full grid gap-10 sm:gap-12 grid-cols-1 lg:grid-cols-2 items-start
          "
        >
          <div className="text-center lg:text-left">
            <p className="font-semibold text-[clamp(1.75rem,3.5vw,3rem)] text-neutral-400">
              BranchDB
            </p>
            <p className="font-light text-[clamp(0.95rem,1.2vw,1.125rem)] text-neutral-500 mt-2">
              A durable, in-memory database built in C++.
            </p>
          </div>

          {/* Links */}
          <nav
            aria-label="Footer"
            className="
              text-neutral-500 grid grid-cols-2 sm:grid-cols-3 gap-8 sm:gap-10 justify-items-start mx-auto lg:mx-0
            "
          >
            {linkSections.map((section) => (
              <div key={section.title} className="flex flex-col gap-3">
                <p className="font-semibold underline underline-offset-4 text-[clamp(1.05rem,1.6vw,1.25rem)]">
                  {section.title}
                </p>
                <ul className="space-y-2">
                  {section.items.map((item) => (
                    <li key={item.label}>
                      <a
                        href={item.href}
                        className="text-[clamp(0.95rem,1.2vw,1rem)] hover:text-white transition"
                      >
                        {item.label}
                      </a>
                    </li>
                  ))}
                </ul>
              </div>
            ))}
          </nav>
        </div>

        {/* Divider */}
        <div className="w-full lg:w-3/4 h-px bg-neutral-700 rounded-full my-8 mx-auto" />

        {/* Copyright */}
        <p className="text-center font-normal text-neutral-500 text-xs sm:text-sm">
          © 2025 BranchDB — Built with C++ | KHAMITKAR SAI CHANDAN
        </p>
      </div>
    </footer>
  );
}
