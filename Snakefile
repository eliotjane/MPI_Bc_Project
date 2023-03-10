#created 24/2/2023
#Eliot Jane Walton

#files_to_be_made = []

#rule all:
#    input: files_to_be_made

rule run_histograms:
    input:
        cut = "Histo_corrector_pT_cut.cpp"
    output:
        "snakemake_test.root"
    shell:
        "root {input.cut} {output} --tname DecayTree"
